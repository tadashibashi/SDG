#include "Shared.h"

#include <SDG/Exceptions/NullReferenceException.h>
#include <SDG/Lib/Memory.h>

namespace SDG
{
    template<typename T>
    inline Shared<T>::Shared(const Shared<T> &other) :
        ptr(other.ptr), count(other.count)
    {
        if (count) ++(*count);
    }

    template<typename T>
    inline Shared<T> &Shared<T>::operator=(const Shared<T> &other)
    {
        if (ptr != other.ptr) // only perform operation if differing ptrs
        {
            Destroy();                      // destroy current
            ptr = other.ptr;
            count = other.count;

            if (count) ++(*count);
        }

        return *this;
    }

    template<typename T>
    inline T *Shared<T>::operator->() const
    {
        if (!ptr) // prevent undefined behavior by throwing
            throw NullReferenceException();
        return ptr;
    }

    template<typename T>
    inline T &Shared<T>::operator*() const
    {
        if (!ptr) // prevent undefined behavior by throwing
            throw NullReferenceException();
        return *ptr;
    }

    template<typename T>
    inline bool Shared<T>::operator==(const Shared &other) const
    {
        return ptr == other.ptr;
    }

    template<typename T>
    inline bool Shared<T>::operator!=(const Shared &other) const
    {
        return ptr != other.ptr;
    }

    template<typename T>
    inline void Shared<T>::Destroy()
    {
        if (count && --(*count) <= 0)
        {
            delete ptr;
            delete count;

            // Don't need since usage is during destruction-like scenarios
            // ptr = nullptr; 
            // count = nullptr;
        }
    }

    template<typename T>
    inline Shared<T>::operator bool() const
    {
        return static_cast<bool>(ptr);
    }
}