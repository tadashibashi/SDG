//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once
#include "Platform.h"
#ifdef SDG_DEBUG

// Use the spdlog static lib
#ifdef SPDLOG_HEADER_ONLY
    #undef SPDLOG_HEADER_ONLY
#endif
#include <spdlog/spdlog.h>

spdlog::logger *GetConsole();

#define SDG_Log(...) GetConsole()->info(__VA_ARGS__)
#define SDG_Err(...) GetConsole()->error(__VA_ARGS__)
#define SDG_Warn(...) GetConsole()->warn(__VA_ARGS__)
#else

#define SDG_Log(...)
#define SDG_Err(...)
#define SDG_Warn(...)

#endif