#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include <android/native_window_jni.h>

class DecodeObserver : public IObserver {
    virtual void Update(XData frame) {
        XLOGI("frame size is : %d", frame.size);
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_weiqianghu_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    DecodeObserver *decodeObserver = new DecodeObserver();

    IDemux *demux = new FFDemux();
    demux->Open("sdcard/1080.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(demux->GetVParameter());
    vdecode->AddObs(decodeObserver);
    demux->AddObs(vdecode);

    IDecode *adecode = new FFDecode();
    adecode->Open(demux->GetAParameter());
    adecode->AddObs(decodeObserver);
    demux->AddObs(adecode);

    demux->Start();
    vdecode->Start();
    adecode->Start();

    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_weiqianghu_xplay_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    XEGL::Get()->Init(win);
    XShader shader;
    shader.Init();
}