#include "Shared.h"
#include <Engine/Exceptions/Fwd.h>

#include <utility>

namespace SDG
{
    // ===== Shared<T>::Impl ==========================================================================================

    template <typename T>
    inline Shared<T>::Impl::Impl(T *newT) : ptr(newT), count(1), deleter([newT]() { delete newT; })
    {

    }

    template <typename T>
    inline Shared<T>::Impl::Impl(T *newT, const std::function<void()> &deleter) : ptr(newT), count(1), deleter(deleter)
    {

    }

    template <typename T>
    inline Shared<T>::Impl::~Impl()
    {
        deleter();
    }

    // ===== Shared<T> ================================================================================================
    template <typename T>
    inline Shared<T>::Shared() : impl(new Impl(nullptr)) { }

    template <typename T>
    inline Shared<T>::Shared(const Shared<T> &other) : impl(other.impl)
    {
        ++impl->count;
    }

    template <typename T>
    inline Shared<T>::Shared(T *newT) : impl(new Impl(newT)) { }

    template <typename T>
    inline Shared<T>::Shared(T *newT, const std::function<void()> &deleter) : impl(new Impl(newT, deleter)) { }

    template <typename T>
    inline Shared<T>::~Shared()
    {
        DestroyRef();
    }

    template <typename T>
    inline Shared<T> &Shared<T>::operator=(const Shared<T> &other)
    {
        if (impl != other.impl) // only perform operation if differing ptrs
        {
            DestroyRef();                      // destroy current
            impl = other.impl;

            ++impl->count;
        }

        return *this;
    }

    template <typename T>
    inline void Shared<T>::DestroyRef()
    {
        if (--impl->count == 0)
            delete impl;
    }
}
