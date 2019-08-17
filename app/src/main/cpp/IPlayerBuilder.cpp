//
// Created by weiqianghu on 2019/8/17.
//

#include "IPlayerBuilder.h"
#include "IDecode.h"
#include "IDemux.h"
#include "IVideoView.h"
#include "IAudioPlay.h"
#include "IResample.h"

IPlayer *IPlayerBuilder::BuildPlayer(unsigned char index) {
    IPlayer *player = CreatePlayer(index);

    IDemux *demux = CreateDemux();

    IDecode *vdecode = CreateDecode();
    demux->AddObs(vdecode);

    IDecode *adecode = CreateDecode();
    demux->AddObs(adecode);

    IVideoView *view = CreateVideoView();
    vdecode->AddObs(view);

    IResample *resample = CreateResample();
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = CreateAudioPlay();
    resample->AddObs(audioPlay);

    player->demux = demux;
    player->vdecode = vdecode;
    player->adecode = adecode;
    player->videoView = view;
    player->resample = resample;
    player->audioPlay = audioPlay;

    return player;
}
