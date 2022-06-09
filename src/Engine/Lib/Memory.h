/// @file Memory.h
/// @namespace SDG
/// Contains functions for safely handling memory allocation on the heap
///
#pragma once
#include <Engine/Exceptions/Fwd.h>
#include <cstdlib>

namespace SDG
{
    /// Allocates memory for a number of objects of type T.
    /// Please be aware that "count" is the number of objects sizeof T, not bytes.
    /// Also, make sure to call Free on the pointer, once the memory is no longer needed.
    /// Throws a RuntimeException if allocation fails.
    /// @param n number of objects of type T to fit in the memory
    template <typename T>
    [[nodiscard]] inline T *Calloc(size_t count)
    {
        T *temp = (T *)malloc(sizeof(T) * count);
        if (!temp)
            ThrowRuntimeException("SDG::Calloc: Out of memory");
        
        return temp;
    }

    [[nodiscard]] inline void *Malloc(size_t bytes)
    {
        void *temp = malloc(bytes);
        if (!temp)
            ThrowRuntimeException("SDG::Malloc: Out of memory");

        return temp;
    }

    /// Copies n objects of type T from the source to the destination
    /// Please be aware that 'n' is the number of objects of sizeof T, not bytes.
    template <typename T>
    inline void Memcpy(T *dest, const T *src, size_t n)
    {
        memcpy(dest, src, sizeof(T) > 0 ? sizeof(T) * n : n);
    }

    /// Safe Realloc function. Throws a RuntimeException when reallocation fails.
    template <typename T = void>
    [[nodiscard]] inline T *Realloc(T *block, size_t size)
    {
        T *temp = (T *)realloc(block, size);
        if (!temp)
            ThrowRuntimeException("SDG::Realloc: Out of memory or pointer "
                "access violation.");
        return temp;
    }

    /// Frees a block of data allocated with SDG::Calloc/SDG::Realloc
    inline void Free(void *block)
    {
        free(block);
    }
}
