//
// Created by weiqianghu on 2019/6/4.
//

#include "IDecode.h"

void IDecode::Main() {

    while (!isExit) {
        packsMutex.lock();
        if (packs.empty()) {
            packsMutex.unlock();
            XSleep(1);
            continue;
        }

        XData pack = packs.front();
        packs.pop_front();

        if (this->SendPacket(pack)) {
            while (!isExit) {
                XData frame = this->RecvFrame();
                if (!frame.data) {
                    break;
                }

                this->Notify(frame);
            }
        }
        pack.Drop();
        packsMutex.unlock();
    }
}

void IDecode::Update(XData pkt) {
    if (pkt.isAudio != isAudio) {
        return;
    }

    while (!isExit) {
        packsMutex.lock();
        if (packs.size() < maxList) {
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        XSleep(1);
    }
}