//
// Created by weiqianghu on 2019/7/2.
//

#ifndef XPLAY_SLAUDIOPLAY_H
#define XPLAY_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay : public IAudioPlay {
public:
    virtual bool StartPlay(XParameter out);

    virtual void Close();

    void PlayCall(void *bufq);

    SLAudioPlay();

    virtual ~SLAudioPlay();

protected:
    unsigned char *buf = 0;
    std::mutex mutex;
};


#endif //XPLAY_SLAUDIOPLAY_H
