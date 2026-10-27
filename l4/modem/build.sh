#!/bin/bash
# Build l4-modemd (L4-M2 virtual AT modem daemon) in CI, reusing the
# vendored aospext toolchain subset in ../toolchain.tar.gz.
# Requires: clang++ in PATH (apt install clang).
set -euo pipefail
DIR=$(cd "$(dirname "$0")" && pwd)
L4_DIR=$(dirname "$DIR")
TOOLCHAIN=${L4_TOOLCHAIN:-$L4_DIR/toolchain}
if [ ! -x "$TOOLCHAIN/aospext_cc" ]; then
  mkdir -p "$TOOLCHAIN"
  tar xzf "$L4_DIR/toolchain.tar.gz" -C "$TOOLCHAIN"
fi
cd "$DIR"
mkdir -p obj out
echo "CC modemd.c"
# NOTE: the compiler's own -c must not be the first passthrough arg —
# aospext_cc's getopts would eat it as its -c option. -O2 first is safe
# (unknown options stop its parsing).
"$TOOLCHAIN/aospext_cc" -c c -d "$TOOLCHAIN/build_flags" -O2 -c "$DIR/modemd.c" -o obj/modemd.o
echo "CXX glibc_shim.cpp"
"$TOOLCHAIN/aospext_cc" -c cxx -d "$TOOLCHAIN/build_flags" \
  -nostdinc++ -I"$TOOLCHAIN/includes/external/libcxx/include" \
  -c "$DIR/glibc_shim.cpp" -o obj/glibc_shim.o
echo "LINK"
# AOSP executable recipe (same as the sensors HAL): Bionic crt objects,
# no driver-default libs, Android linker as interpreter. Guest .so files
# live in $TOOLCHAIN/libs (pulled from the target redroid image).
"$TOOLCHAIN/aospext_cc" -c cxx -d "$TOOLCHAIN/build_flags" \
  "$TOOLCHAIN/objs/crtbegin_dynamic.o" obj/modemd.o obj/glibc_shim.o \
  "$TOOLCHAIN/objs/libc++.vendor.so" \
  "$TOOLCHAIN/libs/liblog.so" "$TOOLCHAIN/libs/libc.so" \
  "$TOOLCHAIN/libs/libm.so" "$TOOLCHAIN/libs/libdl.so" \
  "$TOOLCHAIN/objs/crtend.o" \
  -Wl,--allow-shlib-undefined -nostdlib \
  -Wl,--dynamic-linker,/system/bin/linker64 \
  -o "$DIR/out/l4-modemd"
file "$DIR/out/l4-modemd"
echo BUILD_OK
