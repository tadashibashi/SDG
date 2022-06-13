#include "String.h"
#include <Engine/Exceptions/Fwd.h>
#include <Engine/Lib/Private/Fmt.h>
#include <Engine/Lib/TypeTraits.h>

#include <iomanip>
#include <sstream>
#include <type_traits>
#include <utility>

namespace std
{
    template<>
    inline void swap(SDG::String &a, SDG::String &b) noexcept
    {
        a.Swap(b);
    }
}


template<>
struct fmt::formatter<SDG::String> 
{
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const SDG::String &input, FormatContext &ctx) -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", input.Cstr());
    }
};


namespace SDG
{
    template<typename...Args>
    String String::Format(const char *format, Args ...args)
    {
        auto out = fmt::memory_buffer();
        fmt::vformat_to(std::back_inserter(out), std::string_view(format),
            fmt::make_format_args(args...));
        return { out.data(), out.size() };
    }

    template <typename T>
    T String::ToNumber(uint8_t base) const
    {
        static_assert(std::is_arithmetic_v<T>, "String::ToNumber<T>: type <T> must be arithmetic.");
        
        // make sure the first char is numeric
        size_t pos = FindFirstOf("0123456789abcdefABCDEF-.");
        auto it = begin() + (pos == NullPos ? 0 : pos);
        if (it < end() - 1 && *it == '0' && *(it + 1) == 'x') it += 2; // chop of any prepending "0x", common to hex notation

        String v(&it, end() - it);
        std::stringstream ss; T t;
        ss << std::setbase(base);
        ss << v;
        ss >> t;

        if (ss.fail())
            ThrowRuntimeException(String::Format("String::ToNumber<{}>({}): failed to convert: \"{}\"",
                typeid(T).name(), base, *this));

        return t;
    }

    template<typename T>
    String ToString(const T &t)
    {
        static_assert(is_streamable_v<std::ostream, T>, "SDG::ToString<T>: type T must be streamable to std::ostream");
        return String::Format("{}", t);
    }
}
