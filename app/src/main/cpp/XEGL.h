//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


class XEGL {
public:
    virtual bool Init(void *win) = 0;

    static XEGL *Get();

protected:
    XEGL() {}
};


#endif //XPLAY_XEGL_H
