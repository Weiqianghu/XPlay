//
// Created by weiqianghu on 2019/6/4.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"

class IDecode : public IObserver {
public:
    virtual bool Open(XParameter parameter) = 0;
};


#endif //XPLAY_IDECODE_H
