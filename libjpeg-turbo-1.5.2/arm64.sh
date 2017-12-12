#!/bin/sh
TOOLCHAIN_DIR=aarch64_toolchain

make distclean

$NDK/build/tools/make-standalone-toolchain.sh \
	--install-dir=$TOOLCHAIN_DIR \
	--stl=libc++ \
	--platform=android-21 \
	--toolchain=aarch64-linux-android-4.9 \
	--arch=arm64 \
	--force


HOST=aarch64-linux-android

ANDROID_CFLAGS="-D__ANDROID_API__=21"
TOOLCHAIN=$PWD/$TOOLCHAIN_DIR

export CPP=${TOOLCHAIN}/bin/${HOST}-cpp
export AR=${TOOLCHAIN}/bin/${HOST}-ar
export NM=${TOOLCHAIN}/bin/${HOST}-nm
export CC=${TOOLCHAIN}/bin/${HOST}-gcc
export LD=${TOOLCHAIN}/bin/${HOST}-ld
export RANLIB=${TOOLCHAIN}/bin/${HOST}-ranlib
export OBJDUMP=${TOOLCHAIN}/bin/${HOST}-objdump
export STRIP=${TOOLCHAIN}/bin/${HOST}-strip

sh ./configure --host=${HOST} \
	CFLAGS="${ANDROID_CFLAGS} -O3 -fPIE" \
	CPPFLAGS="${ANDROID_CFLAGS}" \
	LDFLAGS="${ANDROID_CFLAGS} -pie" --with-simd ${1+"$@"}

make
