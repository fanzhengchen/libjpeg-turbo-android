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

typedef u_int8_t BYTE;


jint compressBitmap(JNIEnv *, jclass, jobject, jint, jint, jint, jstring, jboolean);

const int MASK = 255;

const char *CLASS_NAME = "com/xgn/ImageUtil";

const JNINativeMethod jniNativeMethod[] = {
        {"compressBitmap", "(Landroid/graphics/Bitmap;IIILjava/lang/String;Z)I", (void *) compressBitmap}
};

struct error_msg {
    jpeg_error_mgr error_mgr;
    jmp_buf setjmp_buf;
};

int compressJPEG(BYTE *data, int w, int h, int quality, const char *outputPath, bool optimize);

void error_exit(j_common_ptr c_info);

#endif //LIBJPEGTURBODEMO_IMAGEPROC_H
