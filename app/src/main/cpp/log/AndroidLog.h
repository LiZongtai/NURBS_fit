//
// Created by Administrator on 2021/9/6.
//

#ifndef NURBS_FIT_ANDROIDLOG_H
#define NURBS_FIT_ANDROIDLOG_H

#include "android/log.h"

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, "LiZongtai", FORMAT, ##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "LiZongtai", FORMAT, ##__VA_ARGS__);

#endif //NURBS_FIT_ANDROIDLOG_H
