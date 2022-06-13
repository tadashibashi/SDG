/*!
 * @file Logging.h
 * Contains macros for system logging that calls during debug mode.
 *
 */
#pragma once
#include <Engine/Platform.h>

#if (SDG_DEBUG)

#include "Private/spdlog.h"

namespace SDG::Debug
{
    // Used by SDG_Engine
    spdlog::logger *CoreLogger();
    // Available for use by the end user
    spdlog::logger *ClientLogger();
}

#include "LogImpl.h"
#include <Engine/Lib/Concepts.h>
#include <vector>
#include <sstream>
template <typename Ostream, Streamable<Ostream> T>
Ostream &operator << (Ostream &os, const std::vector<T> &v)
{
    static_assert(SDG::is_streamable_v<Ostream, T>, "std::vector<T>: T must be streamable");

    os << "std::vector<" << typeid(T).name() << "> Size:" << v.size() << " [";
    if (!v.empty())
    {
        for (auto it = v.cbegin(), end = v.cend() - 1; it != end; ++it)
            os << *it << ", ";
        os << *(v.cend() - 1);
    }
    os << ']';

    return os;
}

template <Streamable<std::stringstream> T>
struct fmt::formatter< std::vector<T> >
{
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const std::vector<T> &v, FormatContext &ctx) -> decltype(ctx.out())
    {
        std::stringstream ss;
        ss << v;
        return fmt::format_to(ctx.out(), "{}", ss.str());
    }
};

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

#include "Trace.h"
