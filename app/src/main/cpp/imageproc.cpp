#include <jni.h>
#include <string>
#include <setjmp.h>
#include "imageproc.h"
#include <malloc.h>
#include <assert.h>
#include <memory>
#include <android/bitmap.h>
#include "libjpeg-turbo/jpeglib.h"


bool registerNatives(JNIEnv *env) {
    jclass clazz = env->FindClass(CLASS_NAME);
    LOGE("registering");
    if (clazz == NULL) { // not find class
        return false;
    }
    int len = sizeof(jniNativeMethod) /
              sizeof(jniNativeMethod[0]); // count how many java native methods have to be registered
    LOGE("register method %d", len);

    //Returns 0 on success; returns a negative value on failure.
    if (!env->RegisterNatives(clazz, jniNativeMethod, len)) {
        LOGE("register success");
        return true; // register failed
    }
    return false; // register failed
}


extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;

    LOGE("jni onload exec");

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    if (!registerNatives(env)) {//注册
        return -1;
    }
    /* success -- return valid version number */
    result = JNI_VERSION_1_6;

    return result;
}


jint compressBitmap(JNIEnv *env, jclass jclazz, jobject bitmap, jint w, jint h, jint quality,
                    jstring outputFilePath, jboolean optimize) {
    LOGE("compress function called");

    AndroidBitmapInfo bitmapInfo;
    BYTE *pPixels;
    BYTE *data;
    BYTE *tmpData;
    int ret;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo)) < 0) {
        LOGE("AndroidBitmap Get info failed %d", ret);
        return -1;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, (void **) &pPixels))) {
        LOGE("AndroidBitmap lock Pixels failed %d", ret);
        return -1;
    }


    data = (BYTE *) malloc(w * h * 3);

    tmpData = data;

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            int color = *((int *) pPixels);
            BYTE r = (color >> 16) & MASK;
            BYTE g = (color >> 8) & MASK;
            BYTE b = (color) & MASK;
            *data = r;
            ++data;
            *data = g;
            ++data;
            *data = b;
            ++data;
            pPixels += 4;
        }
    }


    AndroidBitmap_unlockPixels(env, bitmap);
    LOGI("bitmap convert %d %d", w, h);

    const char *path = env->GetStringUTFChars(outputFilePath, NULL);
    LOGI("file path %s", path);
    compressJPEG(data, w, h, quality, path, optimize);

    free(tmpData);
    return 0;
}

int compressJPEG(BYTE *data, int w, int h, int quality, const char *outputPath, bool optimize) {

    int nComponents = 3;
    jpeg_compress_struct jcs;

    error_msg errorMsg;
    jcs.err = jpeg_std_error(&errorMsg.error_mgr);

    errorMsg.error_mgr.error_exit = error_exit;

    if (setjmp(errorMsg.setjmp_buf)) {
        return 0;
    }

    jpeg_create_compress(&jcs);
    FILE *file = fopen(outputPath, "wb");
    if (file == NULL) {
        LOGE("open file %s failed", outputPath);
        return 0;
    }
    LOGI("open file %s success", outputPath);

    jpeg_stdio_dest(&jcs, file);

    jcs.image_width = w;
    jcs.image_height = h;

    LOGI("image compress optimize %d", optimize);

    jcs.arith_code = false;
    jcs.input_components = nComponents; // r g b all together is 3

    if (nComponents == 1) {
        jcs.in_color_space = JCS_GRAYSCALE;
    } else {
        jcs.in_color_space = JCS_RGB;
    }

    jpeg_set_defaults(&jcs);
    jcs.optimize_coding = optimize;

    jpeg_set_quality(&jcs, quality, true);

    jpeg_start_compress(&jcs, true);

    JSAMPROW jsamprow[1];
    int row_stride = jcs.image_width * nComponents;

    while (jcs.next_scanline < jcs.image_height) {
        jsamprow[0] = &data[jcs.next_scanline * row_stride];
        jpeg_write_scanlines(&jcs, jsamprow, 1);
    }

    LOGI("optimize %d", jcs.optimize_coding);


    jpeg_finish_compress(&jcs);

    jpeg_destroy_compress(&jcs);

    fclose(file);

    return 1;
}

void error_exit(j_common_ptr info) {
    info->err;
}