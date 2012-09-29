/*
 * common.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#ifdef ANDROID
#include <android/log.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "ohj2710", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "ohj2710", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "ohj2710", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "ohj2710", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "ohj2710", __VA_ARGS__)

#else

#include <stdio.h>

#define LOGV(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)
#define LOGI(...) printf(__VA_ARGS__)
#define LOGW(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)

#endif

#endif /* COMMON_HPP_ */
