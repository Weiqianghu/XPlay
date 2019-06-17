//
// Created by weiqianghu on 2019/6/11.
//

#include "XTexture.h"
#include "XLog.h"
#include "XEGL.h"
#include "XShader.h"

class CXTexture : public XTexture {
public:
    XShader sh;

    virtual bool Init(void *win) {
        if (!win) {
            XLOGE("CXTexture init fail , win is null");
            return false;
        }
        if (!XEGL::Get()->Init(win)) {
            return false;
        }
        sh.Init();

        return true;
    }

    virtual void Draw(unsigned char *data[], int width, int height) {
        sh.GetTexture(0, width, height, data[0]);
        sh.GetTexture(1, width / 2, height / 2, data[1]);
        sh.GetTexture(2, width / 2, height / 2, data[2]);
        sh.Draw();
        XEGL::Get()->Draw();
    }
};

XTexture *XTexture::Create() {
    return new CXTexture();
}
