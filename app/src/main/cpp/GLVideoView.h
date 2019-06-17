//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_GLVIDEOVIEW_H
#define XPLAY_GLVIDEOVIEW_H


#include "XData.h"
#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView {
public:
    virtual void SetRender(void *win);

    virtual void Render(XData xData);

protected:
    void *view = nullptr;
    XTexture *txt = nullptr;
};


#endif //XPLAY_GLVIDEOVIEW_H
