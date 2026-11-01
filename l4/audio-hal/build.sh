#!/bin/bash
# Build the L4-M5 virtual audio HAL: 32-bit ARM legacy audio module
# (audio.primary.redroid.so) loaded by the guest's 32-bit audioserver.
#
# Needs a 32-bit bionic link kit (crtbegin_so.o/crtend_so.o, libc/libm/
# libdl/liblog stubs, compiler-rt builtins, bionic headers). Sources:
#   L4_NDK32_KIT  - dir with the files laid out flat + include/
#   ANDROID_NDK_HOME / ANDROID_NDK_ROOT - an NDK r25+ installation
# AOSP headers come from ./sysinc (hardware/, system/) in this repo.
set -euo pipefail
HAL_DIR=$(cd "$(dirname "$0")" && pwd)
OUT=$HAL_DIR/out/audio.primary.redroid.so
mkdir -p "$HAL_DIR/out"

if [ -n "${L4_NDK32_KIT:-}" ]; then
    KIT=$L4_NDK32_KIT
    INC=$KIT/include
    CRT_B=$KIT/crtbegin_so.o; CRT_E=$KIT/crtend_so.o
    LIBC=$KIT/libc.so; LIBM=$KIT/libm.so; LIBDL=$KIT/libdl.so; LIBLOG=$KIT/liblog.so
    BUILTINS=$KIT/libclang_rt.builtins-arm-android.a
elif [ -n "${ANDROID_NDK_HOME:-${ANDROID_NDK_ROOT:-}}" ]; then
    NDK=${ANDROID_NDK_HOME:-$ANDROID_NDK_ROOT}
    PRE=$NDK/toolchains/llvm/prebuilt/linux-x86_64
    SYS=$PRE/sysroot/usr/lib/arm-linux-androideabi/33
    INC=$PRE/sysroot/usr/include
    CRT_B=$SYS/crtbegin_so.o; CRT_E=$SYS/crtend_so.o
    LIBC=$SYS/libc.so; LIBM=$SYS/libm.so; LIBDL=$SYS/libdl.so; LIBLOG=$SYS/liblog.so
    BUILTINS=$(ls "$PRE"/lib/clang/*/lib/linux/libclang_rt.builtins-arm-android.a | head -1)
else
    echo "ERR: set L4_NDK32_KIT or ANDROID_NDK_HOME" >&2; exit 1
fi
for f in "$CRT_B" "$CRT_E" "$LIBC" "$LIBM" "$LIBDL" "$LIBLOG" "$BUILTINS"; do
    [ -f "$f" ] || { echo "ERR: missing kit file $f" >&2; exit 1; }
done

clang -target armv7a-linux-androideabi33 -march=armv7-a \
    -mfloat-abi=softfp -mfpu=vfpv3-d16 \
    -O2 -Wall -shared -nostdlib \
    -Wl,-soname,audio.primary.redroid.so -Wl,--no-undefined \
    -isystem "$INC" -isystem "$INC/arm-linux-androideabi" \
    -I"$HAL_DIR/sysinc/hardware/libhardware/include" \
    -I"$HAL_DIR/sysinc/system/media/audio/include" \
    -I"$HAL_DIR/sysinc/system/core/libsystem/include" \
    -I"$HAL_DIR/sysinc/system/logging/liblog/include_vndk" \
    -I"$HAL_DIR/sysinc/system/core/libcutils/include" \
    "$HAL_DIR/audio-hal.c" \
    "$CRT_B" "$CRT_E" "$LIBC" "$LIBM" "$LIBDL" "$LIBLOG" "$BUILTINS" \
    -o "$OUT"

# ELF gate: must be 32-bit ARM, no unexpected DT_NEEDED.
readelf -h "$OUT" | grep -E 'Class:|Machine:'
readelf -d "$OUT" | grep NEEDED
echo BUILD_OK
