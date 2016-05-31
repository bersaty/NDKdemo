//
// Created by wuchunhui on 16-5-3.
//
#include "demo_ndkjnidemo_JniUtils.h"
#include<android/bitmap.h>

#include <android/log.h>

JNIEXPORT jstring JNICALL Java_demo_ndkjnidemo_JniUtils_getStringFormC
        (JNIEnv *env, jobject obj) {
    return env->NewStringUTF("这里是来自c++的string");
}

JNIEXPORT void JNICALL Java_demo_ndkjnidemo_JniUtils_setBitmap(JNIEnv *env, jclass type,
                                                               jobject src) {
    // TODO
}

JNIEXPORT void JNICALL Java_demo_ndkjnidemo_JniUtils_render(JNIEnv *env, jclass type, jobject dst) {

    // TODO

}

JNIEXPORT void JNICALL
Java_demo_ndkjnidemo_JniUtils_drop(JNIEnv *env, jclass type, jint x, jint y, jint height) {

    // TODO

}

JNIEXPORT jint JNICALL
Java_demo_ndkjnidemo_JniUtils_processBitmap(JNIEnv *env, jclass type, jobject bmpObj) {

    AndroidBitmapInfo bmpInfo={0};
    __android_log_print(ANDROID_LOG_INFO, "wch JNITag","string From Java To C : %d", AndroidBitmap_getInfo(env,bmpObj,&bmpInfo));
    if(AndroidBitmap_getInfo(env,bmpObj,&bmpInfo)<0)
    {
        return -1;
    }
    int* dataFromBmp=NULL;
    if(AndroidBitmap_lockPixels(env,bmpObj,(void**)&dataFromBmp))
    {
        return -1;
    }

    __android_log_print(ANDROID_LOG_INFO,"wch JNITag","Effect: %dx%d, %d\n", bmpInfo.width, bmpInfo.height, bmpInfo.format);

    AndroidBitmap_unlockPixels(env,bmpObj);
}