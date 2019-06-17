//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H


class XTexture {
public:
    virtual bool Init(void *win) = 0;

    static XTexture *Create();

    virtual void Draw(unsigned char *data[], int width, int height) = 0;
};


#endif //XPLAY_XTEXTURE_H
