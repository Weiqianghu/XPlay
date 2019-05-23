//
// Created by weiqianghu on 2019/5/23.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


#include "IDemux.h"
#include "XLog.h"

class FFDemux : public IDemux {
public:
    virtual bool Open(const char *url);

    virtual XData Read();
};


#endif //XPLAY_FFDEMUX_H
