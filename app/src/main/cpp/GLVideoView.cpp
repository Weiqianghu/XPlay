//
// Created by weiqianghu on 2019/6/11.
//

#include "GLVideoView.h"
#include "XTexture.h"

void GLVideoView::Render(XData xData) {
    if (!view) {
        return;
    }
    if (!txt) {
        txt = XTexture::Create();
        txt->Init(view);
    }
    txt->Draw(xData.datas, xData.width, xData.height);
}

void GLVideoView::SetRender(void *win) {
    view = win;
}