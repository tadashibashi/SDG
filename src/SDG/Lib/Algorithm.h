#pragma once
#include <SDG/Lib/RAIterator.h>
#include <cstddef>
#include <functional>

namespace SDG
{

    /// Perform a callback predicate on RandomAccess Iterators from containers in the SDG library. 
    /// Receives both the value and index.
    /// @param pred - predicate signature: [](const T &value, size_t index)->void
    template <typename T, typename Predicate>
    void foreach(RAIterator<T> begin, RAIterator<T> end, const Predicate &pred)
    {
        static_assert(is_callable_with<Predicate, void(const T &, size_t)>::value, "foreach: predicate must have signature void(const T &value, size_t index)");
        for (RAIterator<T> it = begin; it != end; ++it)
            pred( *it, it.Index() );
    }



    template <typename Iterable>
    inline void foreach(Iterable container, const std::function<void(const std::decay_t<decltype(*std::declval<Iterable>().begin())> &)> &func)
    {
        for (auto &it = container.begin(); it != container.end(); ++it)
            func(*it);
    }

    template <typename It, typename T>
    inline constexpr auto iterator_valtype = ;

    template <typename Iterator>
    inline void foreach(Iterator begin, Iterator end, const std::function<void(const std::decay_t<decltype(*std::declval<Iterator>())> &)> &func)
    {
        for (Iterator &it = begin; it != end; ++it)
            func(*it);
    }
}
