#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include <android/native_window_jni.h>

class DecodeObserver : public IObserver {
    virtual void Update(XData frame) {
        XLOGI("frame size is : %d", frame.size);
    }
};

IVideoView *view = nullptr;

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {
    FFDecode::InitHard(vm);
    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_weiqianghu_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    DecodeObserver *decodeObserver = new DecodeObserver();

    IDemux *demux = new FFDemux();
    demux->Open("sdcard/1080.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(demux->GetVParameter(), true);
    vdecode->AddObs(decodeObserver);
    demux->AddObs(vdecode);

    IDecode *adecode = new FFDecode();
    adecode->Open(demux->GetAParameter());
    adecode->AddObs(decodeObserver);
    demux->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
    XParameter outPara = demux->GetAParameter();
    resample->Open(demux->GetAParameter(), outPara);
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
    audioPlay->StartPlay(outPara);
    resample->AddObs(audioPlay);

    demux->Start();
    vdecode->Start();
    adecode->Start();

    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_weiqianghu_xplay_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    view->SetRender(win);
}