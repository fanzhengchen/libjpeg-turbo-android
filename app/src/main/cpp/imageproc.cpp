#include <jni.h>
#include <string>
#include <setjmp.h>
#include "imageproc.h"
#include <assert.h>
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
    if (!env->RegisterNatives(clazz, jniNativeMethod, len) ) {
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


    return 0;
}