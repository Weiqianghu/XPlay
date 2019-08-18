//
// Created by weiqianghu on 2019/5/23.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


#include "IDemux.h"
#include "XLog.h"
#include <mutex>

struct AVFormatContext;

class FFDemux : public IDemux {
public:
    virtual bool Open(const char *url);

    virtual void Close();

    virtual XParameter GetVParameter();

    virtual XParameter GetAParameter();

    virtual XData Read();

    FFDemux();

private:
    AVFormatContext *ic = 0;
    int audioStream = 1;
    int videoStream = 0;
    std::mutex mutex;
};


#endif //XPLAY_FFDEMUX_H
