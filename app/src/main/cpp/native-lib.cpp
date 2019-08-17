#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "IPlayerProxy.h"

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {
    IPlayerProxy::Get()->Init(vm);

    IPlayerProxy::Get()->Open("sdcard/1080.mp4");
    IPlayerProxy::Get()->Start();

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_weiqianghu_xplay_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(win);
}