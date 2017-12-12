!/bin/sh

TOOLCHAIN_DIR=arm-toolchain
make distclean
rm -rf $TOOLCHAIN_DIR

$NDK/build/tools/make-standalone-toolchain.sh \
	--platform=android-16 \
	--arch=arm \
	--stl=libc++ \
	--toolchain=arm-linux-androideabi \
	--install-dir=$TOOLCHAIN_DIR \
	--force



HOST=arm-linux-androideabi
ANDROID_CFLAGS="-march=armv7-a -mfloat-abi=softfp -fprefetch-loop-arrays -D__ANDROID_API__=16"
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
