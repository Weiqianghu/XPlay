//
// Created by weiqianghu on 2019/7/30.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IVideoView.h"
#include "IAudioPlay.h"
#include "XLog.h"
#include "IResample.h"

IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer player[256];
    return &player[index];
}

IPlayer::IPlayer() {
}

void IPlayer::Main() {
    while (!isExit) {
        mutex.lock();
        if (!audioPlay || !vdecode) {
            mutex.unlock();
            XSleep(2);
            continue;
        }
        int apts = audioPlay->pts;
        XLOGE("apts %d", apts);
        vdecode->synPts = apts;
        mutex.unlock();
        XSleep(2);
    }
}

bool IPlayer::Open(const char *path) {
    mutex.lock();
    if (!demux || !demux->Open(path)) {
        XLOGE("demux open %s failed", path);
        mutex.unlock();
        return false;
    }
    if (!vdecode || !vdecode->Open(demux->GetVParameter(), isHardDecode)) {
        XLOGE("vdecode open %s failed", path);
    }

    if (!adecode || !adecode->Open(demux->GetAParameter())) {
        XLOGE("adecode open %s failed", path);
    }

    if (outPara.sample_rate <= 0) {
        outPara = demux->GetAParameter();
    }
    if (!resample || !resample->Open(demux->GetAParameter(), outPara)) {
        XLOGE("resample open %s failed", path);
    }
    mutex.unlock();
    return true;
}

bool IPlayer::Start() {
    mutex.lock();
    if (!demux || !demux->Start()) {
        XLOGE("demux start failed");
        mutex.unlock();
        return false;
    }
    if (!adecode || !adecode->Start()) {
        XLOGE("adecode start failed");
    }
    if (audioPlay) {
        audioPlay->StartPlay(outPara);
    }

    if (!vdecode || !vdecode->Start()) {
        XLOGE("vdecode start failed");
    }
    XThread::Start();
    mutex.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView) {
        videoView->SetRender(win);
    }
}