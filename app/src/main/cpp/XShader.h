//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();

    virtual void GetTexture(unsigned int index, int width, int height, unsigned char *buf);

    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
};


#endif //XPLAY_XSHADER_H
