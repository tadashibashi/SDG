#include "String.h"
#include <SDG/Lib/Private/Fmt.h>
#include <SDG/Exceptions/Fwd.h>
#include <SDG/Lib/TypeTraits.h>
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

namespace SDG
{
    template<typename...Args>
    String String::Format(const char *format, Args &&...args)
    {
        auto out = fmt::memory_buffer();
        fmt::format_to(std::back_inserter(out), format,
            std::forward<Args>(args)...);
        return { out.data(), out.size() };
    }

    template <typename T>
    T String::To(int base) const
    {
        static_assert(std::is_arithmetic_v<T>, "String::To<T>: type <T> must be arithmetic.");
        
        // make sure the first char is numeric
        auto it = FindIf([](char c) { return isalnum(c) || c == '.'  || c == '-'; });
        if (it < end())
        {
            while (*it == '0') ++it;

            if (it < end())
                while (std::tolower(*it) == 'x') ++it;
        }

        String v(&it, end() - it);
        std::stringstream ss; T t;
        ss << std::setbase(base);
        ss << v;
        ss >> t;

        if (ss.fail())
            ThrowRuntimeException(String::Format("String::To<{}>({}): failed to convert: \"{}\"",
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
