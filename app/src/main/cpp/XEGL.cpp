//
// Created by weiqianghu on 2019/6/11.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include "XEGL.h"
#include "XLog.h"


class CXEGL : public XEGL {
public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    virtual bool Init(void *win) {
        ANativeWindow *nwin = static_cast<ANativeWindow *>(win);

        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            XLOGE("eglGetDisplay failed");
            return false;
        }
        XLOGI("eglGetDisplay success");

        if (EGL_TRUE != eglInitialize(display, nullptr, nullptr)) {
            XLOGE("eglInitialize failed");
            return false;
        }
        XLOGI("eglInitialize success");

        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = nullptr;
        EGLint numConfig;
        if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &numConfig)) {
            XLOGE("eglChooseConfig failed");
            return false;
        }
        XLOGI("eglChooseConfig success");

        surface = eglCreateWindowSurface(display, config, nwin, nullptr);

        const EGLint ctxAttr[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
        };
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            XLOGE("eglCreateContext failed");
            return false;
        }
        XLOGI("eglCreateContext success");

        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            XLOGE("eglMakeCurrent failed");
            return false;
        }
        XLOGI("eglMakeCurrent success");
        return true;
    }
};

XEGL *XEGL::Get() {
    static CXEGL egl;
    return &egl;
}