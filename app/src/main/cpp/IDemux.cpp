//
// Created by weiqianghu on 2019/5/23.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit) {
        XData data = Read();
        if (data.size > 0) {
            Notify(data);
        }
    }
}
