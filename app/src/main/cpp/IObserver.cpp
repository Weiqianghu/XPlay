//
// Created by weiqianghu on 2019/6/3.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver *obs) {
    if (!obs) {
        return;
    }
    mux.lock();
    obss.push_back(obs);
    mux.unlock();
}

void IObserver::Notify(XData xData) {
    mux.lock();
    for (auto &obs : obss) {
        obs->Update(xData);
    }
    mux.unlock();
}