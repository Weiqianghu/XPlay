//
// Created by weiqianghu on 2019/6/24.
//

#include "IResample.h"

void IResample::Update(XData xData) {
    XData data = this->Resample(xData);
    if (data.size > 0) {
        this->Notify(data);
    }
}