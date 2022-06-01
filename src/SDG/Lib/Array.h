#pragma once
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Lib/Memory.h>
#include <cstddef>

namespace SDG
{
    template <typename T>
    class Array
    {
    public:
        Array(const Array &other) :
            arr((size > 0) ? Malloc<T>(size) : nullptr),
            size(other.size)
        {
            Memcpy(arr, other.arr, other.size);
        }

        Array(size_t size = 0) : arr( (size > 0) ? Malloc<T>(size) : nullptr), size(size)
        { }

        Array(const std::initializer_list<T> &list) :
            arr(list.size() > 0 ? Malloc<T>(size) : nullptr), size(list.size())
        {
            T *p = arr;
            for (const T &t : list)
                *p++ = t;
        }

        template <typename FwdIt>
        Array(const FwdIt _begin, const FwdIt _end)
        {
            // Get count
            size_t count = 0;
            for (const FwdIt it = _begin; it != _end; ++it)
            {
                ++count;
            }

            // Allocate memory
            arr = (count > 0) ? Malloc<T>(count) : nullptr;
            size = count;

            // Copy data
            T *ptr = arr;
            for (const FwdIt it = _begin; it != _end; ++it)
            {
                *ptr++ = *it;
            }
        }

        ~Array()
        {
            Free(arr);
        }

        size_t Size() const { return size; }
        bool Empty() const { return arr; }

        typedef T *Iterator;
        typedef const T *ConstIterator;

        Iterator begin() { return arr; }
        Iterator end() { return arr + size; }
        ConstIterator cbegin() const { return arr; }
        ConstIterator cend() const { return arr + size; }

        const T &At(unsigned index) const
        {
            if (index >= size)
                throw OutOfRangeException(index, "Array max index exceeded");
            return arr[size];
        }

        T &At(unsigned index)
        {
            if (index >= size)
                throw OutOfRangeException(index, "Array max index exceeded");
            return arr[size];
        }

        const T &operator[] (unsigned index) const
        {
            return arr[size];
        }

        T &operator[] (unsigned index)
        {
            return arr[size];
        }
        
    private:
        T *arr;
        size_t size;
    };
}