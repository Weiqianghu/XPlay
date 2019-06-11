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

    GetVParameter();
    GetAParameter();
    return true;
}

XData FFDemux::Read() {
    XData xData;
    if (!ic) {
        return xData;
    }
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0) {
        av_packet_free(&pkt);
        return xData;
    }

    xData.data = reinterpret_cast<unsigned char *>(pkt);
    xData.size = pkt->size;
    if (pkt->stream_index == audioStream) {
        xData.isAudio = true;
    } else if (pkt->stream_index == videoStream) {
        xData.isAudio = false;
    } else {
        av_packet_free(&pkt);
        return XData();
    }
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

XParameter FFDemux::GetVParameter() {
    if (!ic) {
        XLOGE("GetVParameter ic is null");
        return XParameter();
    }

    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (re < 0) {
        XLOGE("av_find_best_stream failed");
        return XParameter();
    }
    videoStream = re;

    XParameter parameter;
    parameter.para = ic->streams[re]->codecpar;
    return parameter;
}

XParameter FFDemux::GetAParameter() {
    if (!ic) {
        XLOGE("GetAParameter ic is null");
        return XParameter();
    }

    int re = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    if (re < 0) {
        XLOGE("av_find_best_stream failed");
        return XParameter();
    }
    audioStream = re;

    XParameter parameter;
    parameter.para = ic->streams[re]->codecpar;
    return parameter;
}