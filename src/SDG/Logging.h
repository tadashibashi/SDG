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
#include <string>

namespace SDG::Logging
{
    spdlog::logger *GetConsole();
    void AssertImpl(bool statement, const std::string &statementStr, const char *file, int line, const char *func);
}
#define SDG_Log(...) SDG::Logging::GetConsole()->info(__VA_ARGS__)
#define SDG_Err(...) SDG::Logging::GetConsole()->error(__VA_ARGS__)
#define SDG_Warn(...) SDG::Logging::GetConsole()->warn(__VA_ARGS__)
#define SDG_Assert(statement) (SDG::Logging::AssertImpl(statement, #statement, __FILE__ , __LINE__, __func__))
#else

#define SDG_Log(...)
#define SDG_Err(...)
#define SDG_Warn(...)
#define SDG_Assert(statement, message)
#endif