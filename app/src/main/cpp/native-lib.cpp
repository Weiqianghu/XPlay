#include <jni.h>
#include <string>
#include "FFDemux.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_weiqianghu_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDemux *demux = new FFDemux();
    demux->Open("sdcard/1080.mp4");
    demux->Start();
    XSleep(3000);
    demux->Stop();
    return env->NewStringUTF(hello.c_str());
}
