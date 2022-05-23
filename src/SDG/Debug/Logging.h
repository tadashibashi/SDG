/*!
 * @file Logging.h
 * Contains macros for system logging that calls during debug mode.
 *
 */
#pragma once
#include <SDG/Platform.h>
#if SDG_DEBUG

// Use the spdlog static lib only
#ifdef SPDLOG_HEADER_ONLY
    #undef SPDLOG_HEADER_ONLY
#endif
#include <spdlog/logger.h>

namespace SDG::Debug
{
    spdlog::logger *CoreLogger();
}

#define SDG_Core_Log(...) SDG::Debug::CoreLogger()->info(__VA_ARGS__)
#define SDG_Core_Warn(...) SDG::Debug::CoreLogger()->warn(__VA_ARGS__)
#define SDG_Core_Err(...) SDG::Debug::CoreLogger()->error(__VA_ARGS__)


#elif defined(MSVC)
#define SDG_Core_Log(...) __noop
#define SDG_Core_Warn(...) __noop
#define SDG_Core_Err(...) __noop

#else
#define SDG_Core_Log(...)
#define SDG_Core_Warn(...)
#define SDG_Core_Err(...)


#endif
