//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_IVIDEOVIEW_H
#define XPLAY_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

class IVideoView : public IObserver {
public:
    virtual void SetRender(void *win) = 0;

    virtual void Render(XData xData) = 0;

    virtual void Update(XData xData);
};


#endif //XPLAY_IVIDEOVIEW_H
