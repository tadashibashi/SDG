/*!
 * @file LoggingImpl.h
 * Include this file for each function that implements spdlog logging
 * Example:
 * have a publicly visible function in your class like so:
 *
 */
#pragma once
#include <Engine/Platform.h>

#if (SDG_DEBUG)
#include <spdlog/fmt/ostr.h>
#endif

#include <Engine/Lib/Private/Fmt.h>