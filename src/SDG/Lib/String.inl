#include "String.h"
#include <SDG/Lib/Private/Fmt.h>

#include <utility>

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

    template<typename T>
    String String::Parse(const T &t)
    {
        return Format("{}", t);
    }
}
