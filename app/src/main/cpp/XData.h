//
// Created by weiqianghu on 2019/5/23.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
    unsigned char *data = nullptr;
    int size = 0;

    void Drop();
};


#endif //XPLAY_XDATA_H
