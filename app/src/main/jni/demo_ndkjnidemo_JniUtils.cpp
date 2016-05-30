//
// Created by wuchunhui on 16-5-3.
//
#include "demo_ndkjnidemo_JniUtils.h"

JNIEXPORT jstring JNICALL Java_demo_ndkjnidemo_JniUtils_getStringFormC
        (JNIEnv *env, jobject obj) {
    return env->NewStringUTF("这里是来自c++的string");
}

JNIEXPORT void JNICALL Java_demo_ndkjnidemo_JniUtils_setBitmap(JNIEnv *env, jclass type, jobject src) {
    // TODO
}

JNIEXPORT void JNICALL Java_demo_ndkjnidemo_JniUtils_render(JNIEnv *env, jclass type, jobject dst) {

    // TODO

}

JNIEXPORT void JNICALL
Java_demo_ndkjnidemo_JniUtils_drop(JNIEnv *env, jclass type, jint x, jint y, jint height) {

    // TODO

}