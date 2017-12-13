//
// Created by mark on 17-12-12.
//

#ifndef LIBJPEGTURBODEMO_IMAGEPROC_H
#define LIBJPEGTURBODEMO_IMAGEPROC_H

#include <jni.h>
#include <android/log.h>
#include <libjpeg-turbo/jpeglib.h>


#define LOG_TAG "jni"
#define LOGW(...)  __android_log_write(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

typedef u_int8_t BYTE;


jint compressBitmap2(JNIEnv *, jclass, jobject, jint, jint, jint, jstring, jboolean);

jint compressBitmap(JNIEnv *, jclass, jobject, jint, jstring, jboolean);

const int MASK = 255;

const char *CLASS_NAME = "com/xgn/ImageUtil";

const JNINativeMethod jniNativeMethod[] = {
        {"compressBitmap", "(Landroid/graphics/Bitmap;IIILjava/lang/String;Z)I", (void *) compressBitmap2},
        {"compressBitmap", "(Landroid/graphics/Bitmap;ILjava/lang/String;Z)I",   (void *) compressBitmap}
};

struct my_error_mgr {
    jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

int compressJPEG(BYTE *data, int w, int h, int quality, const char *outputPath, bool optimize);


void error_exit(j_common_ptr c_info);

#endif //LIBJPEGTURBODEMO_IMAGEPROC_H
