//
// Created by weiqianghu on 2019/6/4.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H

#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    virtual bool Open(XParameter parameter);

    virtual bool SendPacket(XData xData);

    virtual XData RecvFrame();

protected:
    AVCodecContext *codec = 0;
    AVFrame *frame = nullptr;
};


#endif //XPLAY_FFDECODE_H
