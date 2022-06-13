#pragma once

#include <map>

namespace SDG
{
    class String;
}

namespace SDG::Dynamic
{
    class Struct
    {
        friend class Object;
        struct Impl;
    public:
        Struct();
        ~Struct();

        Struct(const Struct &s);
        Struct(std::map<String, class Object> map);
        Struct &operator = (const Struct &s);

        [[nodiscard]] const class Object &operator[] (const String &key) const;
        [[nodiscard]] class Object &operator[] (const String &key);

        [[nodiscard]] bool Contains(const String &key) const;

        [[nodiscard]] const std::map<String, class Object> &Members() const;

        [[nodiscard]] bool operator== (const Struct &other) const { return impl == other.impl; }
    private:
        Impl *impl;
    };
}

#include <Engine/Debug/LogImpl.h>
#include <sstream>
std::ostream &operator << (std::ostream &os, const SDG::Dynamic::Struct &obj);

template<>
struct fmt::formatter<SDG::Dynamic::Struct>
{
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const SDG::Dynamic::Struct &input, FormatContext &ctx) -> decltype(ctx.out()) {
        std::stringstream ss;
        ss << input;
        return fmt::format_to(ctx.out(), "{}", ss.str());
    }
};
