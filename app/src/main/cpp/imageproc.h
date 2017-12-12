//
// Created by mark on 17-12-12.
//

#ifndef LIBJPEGTURBODEMO_IMAGEPROC_H
#define LIBJPEGTURBODEMO_IMAGEPROC_H

#include <jni.h>
#include <android/log.h>


#define LOG_TAG "jni"
#define LOGW(...)  __android_log_write(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


jint compressBitmap(JNIEnv *, jclass, jobject, jint, jint, jint, jstring, jboolean);


const char *CLASS_NAME = "com/xgn/ImageUtil";

const JNINativeMethod jniNativeMethod[] = {
        {"compressBitmap", "(Landroid/graphics/Bitmap;IIILjava/lang/String;Z)I", (void *) compressBitmap}
};




#endif //LIBJPEGTURBODEMO_IMAGEPROC_H
