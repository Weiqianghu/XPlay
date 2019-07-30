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

bool IPlayer::Open(const char *path) {
    if (!demux || !demux->Open(path)) {
        XLOGE("demux open %s failed", path);
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

    return true;
}

bool IPlayer::Start() {
    if (!demux || !demux->Start()) {
        XLOGE("demux start failed");
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

    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView) {
        videoView->SetRender(win);
    }
}