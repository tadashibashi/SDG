/// @file Memory.h
/// @namespace SDG
/// Contains functions for safely handling memory allocation on the heap
///
#pragma once
#include <SDG/Exceptions/RuntimeException.h>
#include <cstdlib>

namespace SDG
{
    /// Allocates space for n number of T objects. In other words an array
    /// of T objects with n length is dynamically created.
    /// Throws a RuntimeException if allocation fails.
    /// @param n number of objects of type T to fit in the memory
    template<typename T = void>
    inline T *Malloc(size_t n)
    {
        T *temp = (T *)malloc(sizeof(T) > 0 ? sizeof(T) * n : n);
        if (!temp)
            throw RuntimeException("Malloc: Out of Memory.");
        
        return temp;
    }

    /// Safe Realloc function. Throws a RuntimeException when reallocation fails.
    template<typename T = void>
    inline T *Realloc(T *block, size_t size)
    {
        T *temp = (T *)realloc(block, size);
        if (!temp)
            throw RuntimeException("Realloc: Out of Memory.");

        return temp;
    }

    /// Frees a block of data allocated with SDG::Malloc/SDG::Realloc
    inline void Free(void *block)
    {
        free(block);
    }
}
