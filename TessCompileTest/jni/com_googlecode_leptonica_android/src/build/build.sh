#!/bin/sh

API_LEVEL=14
ABI=armeabi
$ANDROID_SDK/cmake/3.6.4111459/bin/cmake \
	-DANDROID_ABI=$ABI \
	-DANDROID_NATIVE_API_LEVEL=$API_LEVEL \
	-DANDROID_NDK=$NDK \
	-DANDROID_TOOLCHAIN=clang \
	-DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
	-DCMAKE_MAKE_PROGRAM=$HOME/Android/Sdk/cmake/3.6.4111459/bin/ninja \
	-GNinja \
	..
