//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H

enum XTextureType {
    XTEXTURE_YUV420P = 0,
    XTEXTURE_NV12 = 25,
    XTEXTURE_NV21 = 26,
};

class XTexture {
public:
    virtual bool Init(void *win, XTextureType type = XTEXTURE_YUV420P) = 0;

    static XTexture *Create();

    virtual void Draw(unsigned char *data[], int width, int height) = 0;
};


#endif //XPLAY_XTEXTURE_H
