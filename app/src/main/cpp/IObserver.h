//
// Created by weiqianghu on 2019/6/3.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H


#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>

class IObserver : public XThread {
public:
    virtual void Update(XData xData) {}

    void AddObs(IObserver *obs);

    void Notify(XData xData);

protected:
    std::vector<IObserver *> obss;
    std::mutex mux;
};


#endif //XPLAY_IOBSERVER_H
