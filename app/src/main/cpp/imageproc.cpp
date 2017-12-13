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


jint compressBitmap2(JNIEnv *env, jclass jclazz, jobject bitmap, jint w, jint h, jint quality,
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

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, (void **) &pPixels)) < 0) {
        LOGE("AndroidBitmap lock Pixels failed %d", ret);
        return -1;
    }


    data = (BYTE *) malloc(w * h * 3);

    tmpData = data;
    int format = bitmapInfo.format;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
                int color = *((int *) pPixels);
                BYTE r = (color >> 16) & MASK;
                BYTE g = (color >> 8) & MASK;
                BYTE b = (color) & MASK;
                *data = b;
                ++data;
                *data = g;
                ++data;
                *data = r;
                ++data;
                pPixels += 4;
            }
        }
    }


    AndroidBitmap_unlockPixels(env, bitmap);
    LOGI("bitmap convert %d %d %d", bitmapInfo.width, bitmapInfo.height, bitmapInfo.format);

    const char *path = env->GetStringUTFChars(outputFilePath, NULL);
    LOGI("file path %s", path);
    compressJPEG(data, w, h, quality, path, optimize);

    free(tmpData);
    return 0;
}

jint compressBitmap(JNIEnv *env, jclass jclazz, jobject bitmapColor, jint quality,
                    jstring outputFilePath, jboolean optimize) {
    AndroidBitmapInfo androidBitmapInfo;
    BYTE *pixelsColor;
    int ret;
    BYTE *data;
    BYTE *tmpData;
    const char *dstFileName = env->GetStringUTFChars(outputFilePath, NULL);
    //解码Android Bitmap信息
    if ((ret = AndroidBitmap_getInfo(env, bitmapColor, &androidBitmapInfo)) < 0) {
        LOGD("AndroidBitmap_getInfo() failed error=%d", ret);
        return ret;
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmapColor, (void **)&pixelsColor)) < 0) {
        LOGD("AndroidBitmap_lockPixels() failed error=%d", ret);
        return ret;
    }

    LOGD("bitmap: width=%d,height=%d,size=%d , format=%d ",
         androidBitmapInfo.width, androidBitmapInfo.height,
         androidBitmapInfo.height * androidBitmapInfo.width,
         androidBitmapInfo.format);

    BYTE r, g, b;
    int color;

    int w, h, format;
    w = androidBitmapInfo.width;
    h = androidBitmapInfo.height;
    format = androidBitmapInfo.format;

    data = (BYTE *) malloc(androidBitmapInfo.width * androidBitmapInfo.height * 3);
    tmpData = data;
    // 将bitmap转换为rgb数据
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            //只处理 RGBA_8888
            if (format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
                color = (*(int *) (pixelsColor));
                // 这里取到的颜色对应的 A B G R  各占8位
                b = (color >> 16) & 0xFF;
                g = (color >> 8) & 0xFF;
                r = (color >> 0) & 0xFF;
                *data = r;
                *(data + 1) = g;
                *(data + 2) = b;

                data += 3;
                pixelsColor += 4;

            } else {
                return -2;
            }
        }
    }
    AndroidBitmap_unlockPixels(env, bitmapColor);
    //进行压缩
    ret = compressJPEG(tmpData, w, h, quality, dstFileName, optimize);
    free((void *) dstFileName);
    free((void *) tmpData);
    return ret;
    return 0;
}

int compressJPEG(BYTE *data, int w, int h, int quality, const char *outputPath, bool optimize) {

    int nComponent = 3;
    struct jpeg_compress_struct jcs;
    //自定义的error
    struct my_error_mgr jem;

    jcs.err = jpeg_std_error(&jem.pub);
    jem.pub.error_exit = error_exit;

    if (setjmp(jem.setjmp_buffer)) {
        return 0;
    }
    //为JPEG对象分配空间并初始化
    jpeg_create_compress(&jcs);
    //获取文件信息
    FILE *f = fopen(outputPath, "wb");
    if (f == NULL) {
        return 0;
    }

    //指定压缩数据源
    jpeg_stdio_dest(&jcs, f);
    jcs.image_width = w;
    jcs.image_height = h;

    jcs.arith_code = false;
    jcs.input_components = nComponent;
    jcs.in_color_space = JCS_RGB;

    jpeg_set_defaults(&jcs);
    jcs.optimize_coding = optimize;

    //为压缩设定参数，包括图像大小，颜色空间
    jpeg_set_quality(&jcs, quality, true);
    //开始压缩
    jpeg_start_compress(&jcs, true);
    JSAMPROW row_point[1];
    int row_stride;
    row_stride = jcs.image_width * nComponent;
    while (jcs.next_scanline < jcs.image_height) {
        row_point[0] = &data[jcs.next_scanline * row_stride];
        jpeg_write_scanlines(&jcs, row_point, 1);
    }

    if (jcs.optimize_coding) {
        LOGI("使用了哈夫曼算法完成压缩");
    } else {
        LOGI("未使用哈夫曼算法");
    }
    //压缩完毕
    jpeg_finish_compress(&jcs);
    //释放资源
    jpeg_destroy_compress(&jcs);
    fclose(f);
    return 1;
}

void error_exit(j_common_ptr info) {
    info->err;
    LOGE("error exit");
}