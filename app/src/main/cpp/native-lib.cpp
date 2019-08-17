#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "FFPlayerBuilder.h"

static IPlayer *player = nullptr;

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {
    FFPlayerBuilder::InitHard(vm);
    FFPlayerBuilder *ffPlayerBuilder = FFPlayerBuilder::Get();
    player = ffPlayerBuilder->BuildPlayer();

    player->Open("sdcard/1080.mp4");
    player->Start();

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_weiqianghu_xplay_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    if (player) {
        player->InitView(win);
    }
}