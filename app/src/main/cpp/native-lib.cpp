#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "IDecode.h"
#include "FFDecode.h"

class TestObserver : public IObserver {
public:
    void Update(XData xData) {
        XLOGI("TestObserver update size is %d", xData.size);
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_weiqianghu_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    TestObserver *testObserver = new TestObserver();

    IDemux *demux = new FFDemux();
    demux->AddObs(testObserver);
    demux->Open("sdcard/1080.mp4");

    IDecode *decode = new FFDecode();
    decode->Open(demux->GetVParameter());

    demux->Start();
    XSleep(3000);
    demux->Stop();
    return env->NewStringUTF(hello.c_str());
}
