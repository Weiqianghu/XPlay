//
// Created by weiqianghu on 2019/5/23.
//

extern "C" {
#include <libavformat/avformat.h>
}

#include "FFDemux.h"

static double r2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0 : (double) r.num / (double) r.den;
}

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

    pkt->pts = static_cast<int64_t>(pkt->pts * r2d(ic->streams[pkt->stream_index]->time_base) *
                                    1000);
    pkt->dts = static_cast<int64_t>(pkt->dts * r2d(ic->streams[pkt->stream_index]->time_base) *
                                    1000);
    xData.pts = static_cast<int>(pkt->pts);
//    XLOGE("demux pts %d,", xData.pts);
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
    parameter.channels = ic->streams[re]->codecpar->channels;
    parameter.sample_rate = ic->streams[re]->codecpar->sample_rate;

    return parameter;
}