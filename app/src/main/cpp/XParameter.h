//
// Created by weiqianghu on 2019/6/4.
//

#ifndef XPLAY_XPARAMETER_H
#define XPLAY_XPARAMETER_H


struct AVCodecParameters;

class XParameter {
public:
    AVCodecParameters *para = nullptr;
    int channels = 2;
    int sample_rate = 44100;

};


#endif //XPLAY_XPARAMETER_H
