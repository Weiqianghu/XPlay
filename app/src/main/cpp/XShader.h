//
// Created by weiqianghu on 2019/6/11.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H

enum XShaderType {
    XSHADER_YUV420P = 0,
    XSHADER_NV12 = 25,
    XSHADER_NV21 = 26,
};

class XShader {
public:
    virtual bool Init(XShaderType type = XSHADER_YUV420P);

    virtual void
    GetTexture(unsigned int index, int width, int height, unsigned char *buf, bool isA = false);

    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
};


#endif //XPLAY_XSHADER_H
