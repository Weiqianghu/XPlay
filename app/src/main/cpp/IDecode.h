//
// Created by weiqianghu on 2019/6/4.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"
#include <list>

class IDecode : public IObserver {
public:
    virtual bool Open(XParameter parameter, bool isHard = false) = 0;

    virtual bool SendPacket(XData xData) = 0;

    virtual XData RecvFrame() = 0;

    virtual void Update(XData pkt);

    bool isAudio = false;

    int maxList = 100;

protected:
    virtual void Main();

    std::list<XData> packs;
    std::mutex packsMutex;
};


#endif //XPLAY_IDECODE_H
