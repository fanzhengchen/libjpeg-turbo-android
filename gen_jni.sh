#!/usr/bin/env bash
javah -jni -o ./app/src/main/cpp/temp.h -classpath app/build/intermediates/classes/debug:$ANDROID_SDK/platforms/android-26/android.jar com.xgn.ImageUtil
javap -s -classpath app/build/intermediates/classes/debug:$ANDROID_SDK/platforms/android-26/android.jar com.xgn.ImageUtil