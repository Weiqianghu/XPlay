//
// Created by weiqianghu on 2019/7/2.
//

#include "SLAudioPlay.h"
#include "XLog.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

static SLObjectItf objectItf = nullptr;
static SLEngineItf slEngineItf = nullptr;
static SLObjectItf mix = nullptr;
static SLObjectItf player = nullptr;
static SLPlayItf playerItf = nullptr;
static SLAndroidSimpleBufferQueueItf pcmQueue = nullptr;

SLAudioPlay::SLAudioPlay() {
    buf = new unsigned char[1024 * 1024];
}

SLAudioPlay::~SLAudioPlay() {
    delete (buf);
    buf = 0;
}

static SLEngineItf createSL() {
    SLresult sLresult;
    SLEngineItf slEngineItf;
    sLresult = slCreateEngine(&objectItf, 0, nullptr, 0, nullptr, nullptr);
    if (sLresult != SL_RESULT_SUCCESS) {
        return nullptr;
    }

    sLresult = (*objectItf)->Realize(objectItf, SL_BOOLEAN_FALSE);
    if (sLresult != SL_RESULT_SUCCESS) {
        return nullptr;
    }

    sLresult = (*objectItf)->GetInterface(objectItf, SL_IID_ENGINE, &slEngineItf);
    if (sLresult != SL_RESULT_SUCCESS) {
        return nullptr;
    }

    return slEngineItf;
}

static void PcmCall(SLAndroidSimpleBufferQueueItf bf, void *context) {
    if (context == nullptr) {
        XLOGE("PcmCall context is null");
        return;
    }
    SLAudioPlay *ap = static_cast<SLAudioPlay *>(context);
    ap->PlayCall((void *) bf);
}

void SLAudioPlay::PlayCall(void *bufq) {
    if (bufq == nullptr) {
        return;
    }
    SLAndroidSimpleBufferQueueItf bf = static_cast<SLAndroidSimpleBufferQueueItf>(bufq);

    XData data = GetData();
    if (data.size <= 0) {
        XLOGE("Get data size is 0");
        return;
    }

    if (!buf) {
        return;
    }
    memcpy(buf, data.data, static_cast<size_t>(data.size));

    (*bf)->Enqueue(bf, buf, static_cast<SLuint32>(data.size));
    data.Drop();
}

bool SLAudioPlay::StartPlay(XParameter out) {
    slEngineItf = createSL();
    if (slEngineItf) {
        XLOGE("createSL success");
    } else {
        XLOGE("createSL fail");
        return false;
    }

    mix = nullptr;
    SLresult sLresult = (*slEngineItf)->CreateOutputMix(slEngineItf, &mix, 0, nullptr, nullptr);
    if (sLresult != SL_RESULT_SUCCESS) {
        XLOGE("CreateOutputMix fail");
        return false;
    }

    sLresult = (*mix)->Realize(mix, SL_BOOLEAN_FALSE);
    if (sLresult != SL_RESULT_SUCCESS) {
        XLOGE("Realize mix fail");
        return false;
    }
    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, mix};
    SLDataSink audioSink = {&outputMix, nullptr};

    SLDataLocator_AndroidSimpleBufferQueue queue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 10};
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            static_cast<SLuint32>(out.channels),
            static_cast<SLuint32>(out.sample_rate * 1000),
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN
    };
    SLDataSource ds = {&queue, &pcm};

    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[] = {SL_BOOLEAN_FALSE};
    sLresult = (*slEngineItf)->CreateAudioPlayer(slEngineItf, &player, &ds, &audioSink,
                                                 sizeof(ids) / sizeof(SLInterfaceID), ids, req);
    if (sLresult != SL_RESULT_SUCCESS) {
        XLOGE("CreateAudioPlayer fail");
        return false;
    }
    (*player)->Realize(player, SL_BOOLEAN_FALSE);
    sLresult = (*player)->GetInterface(player, SL_IID_PLAY, &playerItf);
    if (sLresult != SL_RESULT_SUCCESS) {
        XLOGE("GetInterface player fail");
        return false;
    }
    sLresult = (*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &pcmQueue);
    if (sLresult != SL_RESULT_SUCCESS) {
        XLOGE("GetInterface SL_IID_BUFFERQUEUE fail");
        return false;
    }

    (*pcmQueue)->RegisterCallback(pcmQueue, PcmCall, this);
    (*playerItf)->SetPlayState(playerItf, SL_PLAYSTATE_PLAYING);

    (*pcmQueue)->Enqueue(pcmQueue, "", 1);
    XLOGD("start play success");
    return true;
}