//
// Created by weiqianghu on 2019/5/23.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H


#include <time64.h>
#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

class IDemux : public IObserver {
public:
    virtual bool Open(const char *url) = 0;

    virtual void Close() = 0;

    virtual XParameter GetVParameter() = 0;

    virtual XParameter GetAParameter() = 0;

    virtual XData Read() = 0;

    int64_t totalMs = 0;
protected:
    virtual void Main();
};


#endif //XPLAY_IDEMUX_H
