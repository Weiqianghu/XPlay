//
// Created by weiqianghu on 2019/5/30.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>

using namespace std;

void XSleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

void XThread::Start() {
    isExit = false;
    thread th(&XThread::ThreadMain, this);
    th.detach();
}

void XThread::ThreadMain() {
    XLOGI("enter ThreadMain");
    isRunning = true;
    Main();
    isRunning = false;
    XLOGI("exit ThreadMain");
}

void XThread::Stop() {
    isExit = true;
    for (int i = 0; i < 200; ++i) {
        if (!isRunning) {
            XLOGI("stop thread success");
            return;
        }
        XSleep(1);
    }
    XLOGI("stop thread timeout");
}
