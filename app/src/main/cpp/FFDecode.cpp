//
// Created by weiqianghu on 2019/6/4.
//

#include "FFDecode.h"
#include "XLog.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/jni.h>
}

void FFDecode::InitHard(void *vm) {
    av_jni_set_java_vm(vm, nullptr);
}

bool FFDecode::Open(XParameter parameter, bool isHard) {
    if (parameter.para == nullptr) {
        return false;
    }
    AVCodecParameters *p = parameter.para;
    AVCodec *cd = nullptr;
    if (isHard) {
        cd = avcodec_find_decoder_by_name("h264_mediacodec");
    } else {
        cd = avcodec_find_decoder(p->codec_id);
    }

    if (!cd) {
        XLOGE("avcodec_find_decoder %d failed,isHard:%d", p->codec_id, isHard);
        return false;
    }
    XLOGI("avcodec_find_decoder %d success,isHard:%d", p->codec_id, isHard);

    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);

    codec->thread_count = 8;
    int re = avcodec_open2(codec, nullptr, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf) - 1);
        XLOGE("avcodec_open2 failed because : %s", buf);
        return false;
    }
    this->isAudio = codec->codec_type == AVMEDIA_TYPE_AUDIO;
    XLOGI("avcodec_open2 success");
    return true;
}

bool FFDecode::SendPacket(XData pkt) {
    if (pkt.size < 0 || !pkt.data) {
        return false;
    }

    if (!codec) {
        return false;
    }

    int re = avcodec_send_packet(codec, reinterpret_cast<const AVPacket *>(pkt.data));
    return re == 0;
}

XData FFDecode::RecvFrame() {
    if (!codec) {
        return XData();
    }
    if (!frame) {
        frame = av_frame_alloc();
    }
    int re = avcodec_receive_frame(codec, frame);
    if (re != 0) {
        return XData();
    }

    XData data;
    data.data = (unsigned char *) frame;
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        data.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        data.width = frame->width;
        data.height = frame->height;
    } else if (codec->codec_type == AVMEDIA_TYPE_AUDIO) {
        data.isAudio = true;
        data.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples *
                    frame->channels;
    }
    data.format = frame->format;
    /*if (!data.isAudio) {
        XLOGI("data format is %d", data.format);
    }*/
    memcpy(data.datas, frame->data, sizeof(data.datas));
    return data;
}