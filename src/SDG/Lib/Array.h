#pragma once
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Lib/Memory.h>

#include <cstddef>
#include <type_traits>

namespace SDG
{
    template <typename T>
    class Array
    {
        static_assert(std::is_default_constructible_v<T>,
            "Array<T>: T must be default constructible");
    public:
        /// Copy constructor
        Array(const Array &other) :
            arr((other.size > 0) ? Malloc<T>(other.size) : nullptr),
            size(other.size)
        {
            Memcpy(arr, other.arr, other.size);
        }

        /// Default constructs "size" number of objects of type T
        Array(size_t size = 0) : arr( (size > 0) ? Malloc<T>(size) : nullptr), size(size)
        {
            for (T &obj : *this)
            {
                T t;
                Memcpy(&obj, &t, 1);
            }     
        }

        /// Copies an initializer list into the Array
        Array(const std::initializer_list<T> &list) :
            arr(list.size() > 0 ? Malloc<T>(list.size()) : nullptr), size(list.size())
        {
            if (arr)
            {
                T *p = arr;
                for (const T &t : list)
                    Memcpy(p++, &t, 1);
            }

        }

        /// Copies elements from a container's forward iterators
        template <typename FwdIt>
        Array(FwdIt _begin, FwdIt _end)
        {
            // Get count
            size_t count = 0;
            for (FwdIt it = _begin; it != _end; ++it)
            {
                ++count;
            }

            // Allocate memory
            arr = (count > 0) ? Malloc<T>(count) : nullptr;
            size = count;

            // Copy data
            T *ptr = arr;
            for (FwdIt it = _begin; it != _end; ++it)
            {
                Memcpy(ptr++, &(*it), 1);
            }
        }

        ~Array()
        {
            Free(arr);
        }

    public:
        /// Number of elements in this array
        size_t Size() const { return size; }
        /// Whether the array has no elements
        bool Empty() const { return !arr; }
        /// Access raw array for copying, but not alteration.
        const T *Data() const { return arr; }

        // ===== Iterators ====================================================
        typedef T *Iterator;
        typedef const T *ConstIterator;

        Iterator begin() { return arr; }
        Iterator end() { return arr + size; }
        ConstIterator cbegin() const { return arr; }
        ConstIterator cend() const { return arr + size; }

        // ===== Indexers =====================================================

        const T &At(unsigned index) const
        {
            if (index >= size)
                throw OutOfRangeException(index, "Array max index exceeded");
            return arr[index];
        }

        T &At(unsigned index)
        {
            if (index >= size)
                throw OutOfRangeException(index, "Array max index exceeded");
            return arr[index];
        }

        const T &operator[] (unsigned index) const
        {
            return arr[index];
        }

        T &operator[] (unsigned index)
        {
            return arr[index];
        }
        
    private:
        T *arr;
        size_t size;
    };
}
