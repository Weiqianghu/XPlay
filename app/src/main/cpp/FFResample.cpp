//
// Created by weiqianghu on 2019/6/24.
//

extern "C" {
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
}

#include "FFResample.h"
#include "XLog.h"

bool FFResample::Open(XParameter in, XParameter out) {
    if (in.para)
        actx = swr_alloc();
    swr_alloc_set_opts(actx, av_get_default_channel_layout(out.channels), AV_SAMPLE_FMT_S16,
                       out.sample_rate,
                       av_get_default_channel_layout(in.para->channels),
                       static_cast<AVSampleFormat>(in.para->format),
                       in.para->sample_rate,
                       0, nullptr);
    int re = swr_init(actx);
    if (re != 0) {
        XLOGE("swr_init failed");
        return false;
    }
    XLOGD("swr_init success");
    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    return true;
}

XData FFResample::Resample(XData xData) {
    if (xData.size <= 0 || !xData.data || !actx) {
        return XData();
    }
    AVFrame *frame = reinterpret_cast<AVFrame *>(xData.data);
    int size = outChannels * frame->nb_samples * av_get_bytes_per_sample(
            static_cast<AVSampleFormat>(outFormat));
    if (size <= 0) {
        return XData();
    }


    XData out;
    out.Alloc(size);

    uint8_t *outArr[2] = {0};
    outArr[0] = out.data;
    int len = swr_convert(actx, outArr, frame->nb_samples,
                          (const uint8_t **) (frame->data), frame->nb_samples);
    if (len <= 0) {
        out.Drop();
        return XData();
    }

    return out;
}