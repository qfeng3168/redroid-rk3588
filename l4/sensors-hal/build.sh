#!/bin/bash
# Build android.hardware.sensors-service.redroid (L4-M1 virtual sensors HAL)
# in CI. Uses the vendored aospext toolchain subset in ../toolchain.tar.gz
# (AOSP headers + crt objects + guest .so files pulled from the target
# redroid image). Requires: clang++ in PATH (apt install clang).
set -euo pipefail
HAL_DIR=$(cd "$(dirname "$0")" && pwd)
L4_DIR=$(dirname "$HAL_DIR")
TOOLCHAIN=${L4_TOOLCHAIN:-$L4_DIR/toolchain}
if [ ! -x "$TOOLCHAIN/aospext_cc" ]; then
  mkdir -p "$TOOLCHAIN"
  tar xzf "$L4_DIR/toolchain.tar.gz" -C "$TOOLCHAIN"
fi
cd "$HAL_DIR"
BNDK=$TOOLCHAIN/includes/frameworks/native/libs/binder/ndk
SYSINC=$TOOLCHAIN/includes/system/core/libcutils/include
INC="-nostdinc++ -I$TOOLCHAIN/includes/external/libcxx/include -I$HAL_DIR/gen/include -I$HAL_DIR/fmq-include -I$BNDK/include_ndk -I$BNDK/include_cpp -I$BNDK/include_platform -I$SYSINC -I$TOOLCHAIN/includes/system/libfmq/base -I$TOOLCHAIN/includes/system/libbase/include -I$TOOLCHAIN/includes/system/core/libutils/include -I$TOOLCHAIN/includes/system/logging/liblog/include_vndk -include assert.h -include string.h -include errno.h -include atomic -include cstdint -DPAGE_SIZE=4096 -march=armv8.2-a"
mkdir -p obj out
OBJS=""
while IFS= read -r f; do
  o="obj/$(echo "$f" | tr '/' '_').o"
  echo "CXX $f"
  "$TOOLCHAIN/aospext_cc" -c cxx -d "$TOOLCHAIN/build_flags" $INC -c "$f" -o "$o"
  OBJS="$OBJS $o"
done < <(find "$HAL_DIR/gen/src" -name '*.cpp'; echo "$HAL_DIR/Sensors.cpp"; echo "$HAL_DIR/main.cpp"; echo "$HAL_DIR/glibc_shim.cpp")
echo "LINK"
# AOSP executable recipe: Bionic crtbegin/crtend, no driver-default libs,
# Android linker as interpreter. $TOOLCHAIN/libs holds .so files pulled
# from the target redroid guest (real APEX files).
"$TOOLCHAIN/aospext_cc" -c cxx -d "$TOOLCHAIN/build_flags" \
  "$TOOLCHAIN/objs/crtbegin_dynamic.o" $OBJS \
  "$TOOLCHAIN/objs/libc++.vendor.so" \
  "$TOOLCHAIN/libs/libbinder_ndk.so" "$TOOLCHAIN/libs/libfmq.so" "$TOOLCHAIN/libs/libbase.so" \
  "$TOOLCHAIN/libs/libbinder.so" "$TOOLCHAIN/libs/libcutils.so" "$TOOLCHAIN/libs/libutils.so" \
  "$TOOLCHAIN/libs/liblog.so" "$TOOLCHAIN/libs/libc.so" "$TOOLCHAIN/libs/libm.so" \
  "$TOOLCHAIN/libs/libdl.so" "$TOOLCHAIN/objs/crtend.o" \
  -Wl,--allow-shlib-undefined -nostdlib \
  -Wl,--dynamic-linker,/system/bin/linker64 \
  -o "$HAL_DIR/out/android.hardware.sensors-service.redroid"
file "$HAL_DIR/out/android.hardware.sensors-service.redroid"
echo BUILD_OK
