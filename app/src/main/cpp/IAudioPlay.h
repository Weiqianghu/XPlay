//
// Created by weiqianghu on 2019/7/2.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    virtual void Update(XData data);

    virtual XData GetData();

    virtual bool StartPlay(XParameter out) = 0;

    int maxFrame = 100;

    int pts = 0;

protected:
    std::list<XData> frames;
    std::mutex framesMutex;
};


#endif //XPLAY_IAUDIOPLAY_H
