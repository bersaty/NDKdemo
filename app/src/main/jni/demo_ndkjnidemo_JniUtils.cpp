//
// Created by wuchunhui on 16-5-3.
//
#include "demo_ndkjnidemo_JniUtils.h"
#include<android/bitmap.h>

#include <android/log.h>


#define RGB565_R(p) ((((p) & 0xF800) >> 11) << 3)
#define RGB565_G(p) ((((p) & 0x7E0 ) >> 5)  << 2)
#define RGB565_B(p) ( ((p) & 0x1F  )        << 3)
#define MAKE_RGB565(r,g,b) ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))

#define RGBA_A(p) (((p) & 0xFF000000) >> 24)
#define RGBA_R(p) (((p) & 0x00FF0000) >> 16)
#define RGBA_G(p) (((p) & 0x0000FF00) >>  8)
#define RGBA_B(p)  ((p) & 0x000000FF)
#define MAKE_RGBA(r,g,b,a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

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
    __android_log_print(ANDROID_LOG_INFO, "wch AndroidBitmap_getInfo "," : %d", AndroidBitmap_getInfo(env,bmpObj,&bmpInfo));
    if(AndroidBitmap_getInfo(env,bmpObj,&bmpInfo)<0)
    {
        return -1;
    }
    int* dataFromBmp=NULL;
    if(AndroidBitmap_lockPixels(env,bmpObj,(void**)&dataFromBmp))
    {
        return -1;
    }

    /*************************转换成灰度图************************/
    int x = 0, y = 0;
    // From top to bottom
    for (y = 0; y < bmpInfo.height; ++y) {
        // From left to right
        for (x = 0; x < bmpInfo.width; ++x) {
            int a = 0, r = 0, g = 0, b = 0;
            void *pixel = NULL;
            // Get each pixel by format
            if (bmpInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
                pixel = ((uint16_t *)dataFromBmp) + y * bmpInfo.width + x;
                uint16_t v = *(uint16_t *)pixel;
                r = RGB565_R(v);
                g = RGB565_G(v);
                b = RGB565_B(v);
            } else {// RGBA
                pixel = ((uint32_t *)dataFromBmp) + y * bmpInfo.width + x;
                uint32_t v = *(uint32_t *)pixel;
                a = RGBA_A(v);
                r = RGBA_R(v);
                g = RGBA_G(v);
                b = RGBA_B(v);
            }

            // Grayscale
            int gray = (r * 38 + g * 75 + b * 15) >> 7;

            // Write the pixel back
            if (bmpInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
                *((uint16_t *)pixel) = MAKE_RGB565(gray, gray, gray);
            } else {// RGBA
                *((uint32_t *)pixel) = MAKE_RGBA(gray, gray, gray, a);
            }
        }
    }
    /*************************转换成灰度图************************/

    __android_log_print(ANDROID_LOG_INFO,"wch JNITag","Effect: %dx%d, %d\n", bmpInfo.width, bmpInfo.height, bmpInfo.format);

    __android_log_print(ANDROID_LOG_INFO, "wch dataFromBmp","  : %u", dataFromBmp[0]);

    AndroidBitmap_unlockPixels(env,bmpObj);
}