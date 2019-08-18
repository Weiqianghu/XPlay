//
// Created by weiqianghu on 2019/6/24.
//

#ifndef XPLAY_FFRESAMPLE_H
#define XPLAY_FFRESAMPLE_H


#include "IResample.h"

struct SwrContext;

class FFResample : public IResample {
public:
    virtual bool Open(XParameter in, XParameter out = XParameter());

    virtual void Close();

    virtual XData Resample(XData xData);

protected:
    SwrContext *actx = 0;
    std::mutex mutex;
};


#endif //XPLAY_FFRESAMPLE_H
