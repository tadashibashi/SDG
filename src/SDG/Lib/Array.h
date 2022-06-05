#pragma once
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace SDG
{
    /// Contains a contiguous array of objects. Elements must be copy-constructible and swappable.
    template <typename T>
    class Array
    {
        static_assert(std::is_copy_constructible_v<T>,
            "Array<T>: T must be default constructible");
        static_assert(std::is_swappable_v<T>,
            "Array<T>: T must be swappable");
    public:
        /// Copy constructor
        Array(const Array<T> &other);

        /// Default constructs "size" number of objects of type T
        Array(size_t size = 0);

        /// Copies an initializer list into the Array
        Array(const std::initializer_list<T> &list);

        /// Copies elements from a container's forward iterators
        template <typename FwdIt>
        Array(FwdIt _begin, FwdIt _end);

        ~Array() { Free(arr); }

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

        /// Gets a reference to an object at array index. Checks bounds and
        /// throws an OutOfRangeException if outside array bounds.
        const T &At(unsigned index) const;

        /// Gets a reference to an object at array index. Checks bounds and
        /// throws an OutOfRangeException if outside array bounds.
        T &At(unsigned index);

        /// Gets a reference to an object at array index. No bounds checks.
        const T &operator[] (unsigned index) const { return arr[index]; }

        /// Gets a reference to an object at array index. No bounds checks.
        T &operator[] (unsigned index) { return arr[index]; }
        
    private:
        T *arr;
        size_t size;
    };
}

#include "Array.inl"
