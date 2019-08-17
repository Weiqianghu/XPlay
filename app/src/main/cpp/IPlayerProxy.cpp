//
// Created by weiqianghu on 2019/8/17.
//

#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"

void IPlayerProxy::Init(void *vm) {
    mutex.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player) {
        player = FFPlayerBuilder::Get()->BuildPlayer();
    }
    mutex.unlock();
}

void IPlayerProxy::InitView(void *win) {
    mutex.lock();
    if (player) {
        player->InitView(win);
    }
    mutex.unlock();
}

bool IPlayerProxy::Open(const char *path) {
    bool result = false;
    mutex.lock();
    if (player) {
        result = player->Open(path);
    }
    mutex.unlock();
    return result;
}

bool IPlayerProxy::Start() {
    bool result = false;
    mutex.lock();
    if (player) {
        result = player->Start();
    }
    mutex.unlock();
    return result;
}
