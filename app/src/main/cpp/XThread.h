//
// Created by weiqianghu on 2019/5/30.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

void XSleep(int mis);

class XThread {
public:
    virtual bool Start();

    virtual void Stop();

    virtual void Main() {};
protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void ThreadMain();
};


#endif //XPLAY_XTHREAD_H
