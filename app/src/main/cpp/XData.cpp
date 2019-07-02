//
// Created by weiqianghu on 2019/5/23.
//

#include "XData.h"

extern "C" {
#include "include/libavcodec/avcodec.h"
}

bool XData::Alloc(int size, const char *data) {
    Drop();
    type = UCHAR_TYPE;
    if (size <= 0) {
        return false;
    }
    this->data = new unsigned char[size];
    this->size = size;
    if (!this->data) {
        return false;
    }
    if (data) {
        memcpy(this->data, data, size);
    }
    return true;
}

void XData::Drop() {
    if (data == nullptr) {
        return;
    }

    if (type == AVPACKET_TYPE) {
        av_packet_free(reinterpret_cast<AVPacket **>(&data));
    } else {
        delete data;
    }
    data = nullptr;
    size = 0;
}