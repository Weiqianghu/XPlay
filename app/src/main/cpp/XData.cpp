//
// Created by weiqianghu on 2019/5/23.
//

#include "XData.h"

extern "C" {
#include "include/libavcodec/avcodec.h"
}

void XData::Drop() {
    if (data != nullptr) {
        av_packet_free(reinterpret_cast<AVPacket **>(&data));
        data = nullptr;
        size = 0;
    }
}