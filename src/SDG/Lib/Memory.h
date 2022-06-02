/// @file Memory.h
/// @namespace SDG
/// Contains functions for safely handling memory allocation on the heap
///
#pragma once
#include <SDG/Exceptions/RuntimeException.h>

#include <cstdlib>

namespace SDG
{
    /// Allocates memory for n objects of type T.
    /// Please be aware that 'n' is the number of objects sizeof T, not bytes.
    /// If raw bytes are needed, use "void" for the template parameter.
    /// Also, make sure to call Free on the pointer, once the memory is no longer needed.
    /// Throws a RuntimeException if allocation fails.
    /// @param n number of objects of type T to fit in the memory
    template <typename T = void>
    [[nodiscard]] inline T *Malloc(size_t n)
    {
        T *temp = (T *)malloc(sizeof(T) > 0 ? sizeof(T) * n : n);
        if (!temp)
            throw RuntimeException("Malloc: Out of memory.");
        
        return temp;
    }

    /// Copies n objects of type T from the source to the destination
    /// Please be aware that 'n' is the number of objects of sizeof T, not bytes.
    /// If raw bytes are needed, use "void" for the template parameter
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
            throw RuntimeException("SDG::Realloc: Out of memory or pointer "
                "access violation.");
        return temp;
    }

    /// Frees a block of data allocated with SDG::Malloc/SDG::Realloc
    inline void Free(void *block)
    {
        free(block);
    }
}
