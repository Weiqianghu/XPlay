//
// Created by weiqianghu on 2019/6/4.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H

#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;

class FFDecode : public IDecode {
public:
    virtual bool Open(XParameter parameter);

protected:
    AVCodecContext *codec = 0;
};


#endif //XPLAY_FFDECODE_H
