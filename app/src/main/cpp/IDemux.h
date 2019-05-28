//
// Created by weiqianghu on 2019/5/23.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H


#include <time64.h>
#include "XData.h"

class IDemux {
public:
    virtual bool Open(const char *url) = 0;

    virtual XData Read() = 0;

    int64_t totalMs = 0;
};


#endif //XPLAY_IDEMUX_H
