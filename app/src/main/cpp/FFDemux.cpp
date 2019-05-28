//
// Created by weiqianghu on 2019/5/23.
//

extern "C" {
#include <libavformat/avformat.h>
}

#include "FFDemux.h"

bool FFDemux::Open(const char *url) {
    XLOGD("start open");
    int re = avformat_open_input(&ic, url, nullptr, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDemux open %s failed,because:%s", url, buf);
        return false;
    }
    XLOGI("FFDemux open %s success", url);

    re = avformat_find_stream_info(ic, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDemux avformat_find_stream_info %s failed,because:%s", url, buf);
        return false;
    }

    totalMs = ic->duration / (AV_TIME_BASE / 1000);
    XLOGI("FFDemux avformat_find_stream_info %s success,totalMs:%lld", url, totalMs);
    return true;
}

XData FFDemux::Read() {
    XData xData;
    return xData;
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        av_register_all();
        avcodec_register_all();
        avformat_network_init();
        XLOGD("register ffmpeg success");
    }
}