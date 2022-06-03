/*!
 * @file Logging.h
 * Contains macros for system logging that calls during debug mode.
 *
 */
#pragma once
#include <SDG/Lib/Platform.h>

#if (SDG_DEBUG)

// Use the spdlog static lib only
#ifdef SPDLOG_HEADER_ONLY
    #undef SPDLOG_HEADER_ONLY
#endif
#include <spdlog/logger.h>

namespace SDG::Debug
{
    // Used by SDG_Engine
    spdlog::logger *CoreLogger();
    // Available for use by the end user
    spdlog::logger *ClientLogger();
}
// Engine logging
#define SDG_Core_Log(...) SDG::Debug::CoreLogger()->info(__VA_ARGS__)
#define SDG_Core_Warn(...) SDG::Debug::CoreLogger()->warn(__VA_ARGS__)
#define SDG_Core_Err(...) SDG::Debug::CoreLogger()->error(__VA_ARGS__)

// Client logging
#define SDG_Log(...) SDG::Debug::ClientLogger()->info(__VA_ARGS__)
#define SDG_Warn(...) SDG::Debug::ClientLogger()->warn(__VA_ARGS__)
#define SDG_Err(...) SDG::Debug::ClientLogger()->error(__VA_ARGS__)

#elif defined(MSVC)
#define SDG_Core_Log(...) __noop
#define SDG_Core_Warn(...) __noop
#define SDG_Core_Err(...) __noop
#define SDG_Log(...) __noop
#define SDG_Warn(...) __noop
#define SDG_Err(...) __noop

#else
#define SDG_Core_Log(...)
#define SDG_Core_Warn(...)
#define SDG_Core_Err(...)
#define SDG_Log(...)
#define SDG_Warn(...)
#define SDG_Err(...)

#endif
