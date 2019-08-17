//
// Created by weiqianghu on 2019/8/17.
//

#ifndef XPLAY_IPLAYERPROXY_H
#define XPLAY_IPLAYERPROXY_H

#include "IPlayer.h"
#include <mutex>

class IPlayerProxy : public IPlayer {
public:
    static IPlayerProxy *Get() {
        static IPlayerProxy proxy;
        return &proxy;
    }

    void Init(void *vm = 0);

    virtual bool Open(const char *path);

    virtual bool Start();

    virtual void InitView(void *win);

protected:
    IPlayerProxy() {};

    IPlayer *player = 0;
    std::mutex mutex;
};


#endif //XPLAY_IPLAYERPROXY_H
