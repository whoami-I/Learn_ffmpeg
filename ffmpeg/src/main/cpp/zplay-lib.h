//
// Created by user on 20-8-14.
//

#ifndef LEARN_FMPEG_ZPLAY_LIB_H
#define LEARN_FMPEG_ZPLAY_LIB_H

#include <jni.h>
#ifdef  __cplusplus
extern "C" {
#endif

JNIEXPORT void
JNICALL Java_com_zasko_ffmpeg_RenderManager_pcm2Wav(JNIEnv *env, jclass type);

JNIEXPORT void
JNICALL
Java_com_zasko_ffmpeg_RenderManager_playFile(JNIEnv *env, jclass type, jstring filePath);

JNIEXPORT jstring
JNICALL
Java_com_zasko_ffmpeg_RenderManager_getConfig(JNIEnv *env, jclass type);

JNIEXPORT jstring JNICALL
Java_com_example_learn_1fmpeg_MainActivity_getConfig(JNIEnv *env, jobject thiz);

};

#endif