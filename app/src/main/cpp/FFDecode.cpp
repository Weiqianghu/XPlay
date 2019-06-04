//
// Created by weiqianghu on 2019/6/4.
//

#include "FFDecode.h"
#include "XLog.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

bool FFDecode::Open(XParameter parameter) {
    if (parameter.para == nullptr) {
        return false;
    }
    AVCodecParameters *p = parameter.para;
    AVCodec *cd = avcodec_find_decoder(p->codec_id);
    if (!cd) {
        XLOGE("avcodec_find_decoder %d failed", p->codec_id);
        return false;
    }
    XLOGI("avcodec_find_decoder %d success", p->codec_id);

    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);

    int re = avcodec_open2(codec, nullptr, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf) - 1);
        XLOGE("avcodec_open2 failed because : %s", buf);
        return false;
    }
    XLOGI("avcodec_open2 success");
    return true;
}