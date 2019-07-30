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
#include "IPlayer.h"
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
    DecodeObserver *decodeObserver = new DecodeObserver();

    IDemux *demux = new FFDemux();

    IDecode *vdecode = new FFDecode();
    vdecode->AddObs(decodeObserver);
    demux->AddObs(vdecode);

    IDecode *adecode = new FFDecode();
    adecode->AddObs(decodeObserver);
    demux->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
    resample->AddObs(audioPlay);

    IPlayer::Get()->demux = demux;
    IPlayer::Get()->vdecode = vdecode;
    IPlayer::Get()->adecode = adecode;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = audioPlay;
    IPlayer::Get()->Open("sdcard/1080.mp4");
    IPlayer::Get()->Start();

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_weiqianghu_xplay_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayer::Get()->InitView(win);
}