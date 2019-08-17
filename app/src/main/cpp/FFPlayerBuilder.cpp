//
// Created by weiqianghu on 2019/8/17.
//

#include "FFPlayerBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include "SLAudioPlay.h"

IDemux *FFPlayerBuilder::CreateDemux() {
    IDemux *ff = new FFDemux();
    return ff;
}

IDecode *FFPlayerBuilder::CreateDecode() {
    IDecode *ff = new FFDecode();
    return ff;
}

IVideoView *FFPlayerBuilder::CreateVideoView() {
    IVideoView *gl = new GLVideoView();
    return gl;
}

IResample *FFPlayerBuilder::CreateResample() {
    IResample *ff = new FFResample();
    return ff;
}

IAudioPlay *FFPlayerBuilder::CreateAudioPlay() {
    IAudioPlay *sl = new SLAudioPlay();
    return sl;
}

IPlayer *FFPlayerBuilder::CreatePlayer(unsigned char index) {
    return IPlayer::Get(index);
}

void FFPlayerBuilder::InitHard(void *vm) {
    FFDecode::InitHard(vm);
}