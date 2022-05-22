#pragma once
#include <type_traits>

namespace SDG
{
    template <typename T>
    void Swap(T &a, T &b)
    {
        static_assert(std::is_copy_assignable_v<T>,
            "Please specialize this function for unique cases");
        T temp = a;
        a = b;
        b = temp;
    }
}
