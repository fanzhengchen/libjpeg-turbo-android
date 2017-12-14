#!/bin/sh
ABI=armeabi-v7a
rm -rf $ABI
mkdir=$ABI
$ANDROID_SDK/cmake/3.6.4111459/bin/cmake \
	-DANDROID_NDK=$NDK \
	-DANDROID_PLATFORM=16 \
	-DCMAKE_BUILD_TYPE=Debug \
	-DANDROID_ABI=$ABI \
	-G"Android Gradle - Ninja" \
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$ABI \
	-DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
	-DCMAKE_CXX_FLAGS="" \
	..
#$ANDROID_SDK/cmake/3.6.4111459/bin/cmake --build .

