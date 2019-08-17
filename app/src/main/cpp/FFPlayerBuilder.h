//
// Created by weiqianghu on 2019/8/17.
//

#ifndef XPLAY_FFPLAYERBUILDER_H
#define XPLAY_FFPLAYERBUILDER_H

#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder {
public:
    static void InitHard(void *vm);
    static FFPlayerBuilder *Get() {
        static FFPlayerBuilder ffPlayerBuilder;
        return &ffPlayerBuilder;
    }

protected:
    FFPlayerBuilder() {};

    virtual IDemux *CreateDemux();

    virtual IDecode *CreateDecode();

    virtual IResample *CreateResample();

    virtual IVideoView *CreateVideoView();

    virtual IAudioPlay *CreateAudioPlay();

    virtual IPlayer *CreatePlayer(unsigned char index = 0);
};


#endif //XPLAY_FFPLAYERBUILDER_H
