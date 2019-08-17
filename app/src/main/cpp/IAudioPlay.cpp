//
// Created by weiqianghu on 2019/7/2.
//

#include "IAudioPlay.h"
#include "XLog.h"

XData IAudioPlay::GetData() {
    XData data;

    while (!isExit) {
        framesMutex.lock();
        if (!frames.empty()) {
            data = frames.front();
            frames.pop_front();
            pts = data.pts;
            framesMutex.unlock();
            return data;
        }
        framesMutex.unlock();
        XSleep(1);
        framesMutex.unlock();
    }
    return data;
}

void IAudioPlay::Update(XData data) {
    if (data.size <= 0 || !data.data) {
        return;
    }
    XLOGI("IAudioPlay::Update data.size : %d", data.size);
    while (!isExit) {
        framesMutex.lock();
        if (frames.size() > maxFrame) {
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        break;
    }

}