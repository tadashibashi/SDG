#include "Array.h"
#include <SDG/Lib/Memory.h>
#include <SDG/Exceptions/Fwd.h>
#include <utility>

namespace SDG
{
    template<typename T>
    Array<T>::~Array() { Free(arr); }

    template<typename T>
    Array<T>::Array(const Array<T> &other) :
        arr((other.size > 0) ? Calloc<T>(other.size) : nullptr),
        size(other.size)
    {
        if (size > 0)
        {
            memset(arr, 0, sizeof(T) * size); // sets everything value to 0/null

            T *p = arr;
            for (Array<T>::ConstIterator it = other.cbegin(), end = other.cend(); it != end; ++it)
            {
                T temp(*it);
                std::swap(temp, *p++);
            }
        }
    }

    template<typename T>
    Array<T>::Array(size_t size) : arr((size > 0) ? Calloc<T>(size) : nullptr), size(size)
    {
        if (arr)
        {
            memset(arr, 0, sizeof(T) * size);
            for (T &obj : *this)
            {
                T t{};
                std::swap(t, obj);
            }
        }
    }

    template<typename T>
    Array<T>::Array(const std::initializer_list<T> &list) :
        arr(list.size() > 0 ? Calloc<T>(list.size()) : nullptr), size(list.size())
    {
        if (arr)
        {
            memset(arr, 0, size * sizeof(T));

            T *p = arr;
            for (const T &t : list)
            {
                T temp(t);
                std::swap(temp, *p++);
            }
        }
    }

    template<typename T>
    template <typename FwdIt>
    Array<T>::Array(FwdIt _begin, FwdIt _end) 
    {
        static_assert(std::is_same_v<T, std::decay_t<decltype(*_begin)>>,
            "ForwardIterator must contain Array's type T");

        // Get count
        size_t count = 0;
        for (FwdIt it = _begin; it != _end; ++it)
            ++count;

        // Allocate memory
        arr = (count > 0) ? Calloc<T>(count) : nullptr;
        memset(arr, 0, count * sizeof(T));
        size = count;

        // Copy data
        T *ptr = arr;
        for (FwdIt it = _begin; it != _end; ++it)
        {
            T temp(*it);
            std::swap(temp, *ptr++);
        }
    }

    template<typename T>
    const T &Array<T>::At(unsigned index) const
    {
        if (index >= size)
            ThrowOutOfRangeException(index, "Array max index exceeded");
        return arr[index];
    }

    template<typename T>
    T &Array<T>::At(unsigned index)
    {
        if (index >= size)
            ThrowOutOfRangeException(index, "Array max index exceeded");
        return arr[index];
    }
}