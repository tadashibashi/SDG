#include "StringView.h"

#include <iomanip>
#include <sstream>
#include <typeinfo>

namespace SDG
{
    template <typename T>
    T StringView::ToNumber(int base) const
    {
        static_assert(std::is_arithmetic_v<T>, "StringView::ToNumber<T>: type T must be arithmetic.");

        // make sure the first char is numeric
        auto it = begin() + FindFirstOf("0123456789abcdefABCDEF-.");
        if (it < end() - 1 && *it == '0' && *(it + 1) == 'x') it += 2; // chop of any prepending "0x", common to hex notation

        StringView v(&it, end() - it);
        std::stringstream ss; T t;
        ss << std::setbase(base);
        ss << v;
        ss >> t;

        if (ss.fail())
            ThrowRuntimeException(String::Format("StringView::ToNumber<{}>({}): failed to convert: \"{}\"",
                typeid(T).name(), base, *this));

        return t;
    }
}
