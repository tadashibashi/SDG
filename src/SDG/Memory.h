#pragma once
#include <SDG/Exceptions/RuntimeException.h>
#include <cstdlib>

namespace SDG
{
    /// Safe Malloc function. Throws a RuntimeException when allocation fails.
    template<typename T = void>
    T *Malloc(size_t n)
    {
        T *temp = (T *)malloc(sizeof(T) > 0 ? sizeof(T) * n : n);
        if (!temp)
            throw RuntimeException("Malloc: Out of Memory.");
        
        return temp;
    }

    /// Safe Realloc function. Throws a RuntimeException when reallocation fails.
    template<typename T = void>
    T *Realloc(T *block, size_t size)
    {
        T *temp = (T *)realloc(block, size);
        if (!temp)
            throw RuntimeException("Realloc: Out of Memory.");

        return temp;
    }

    /// Frees a block of data allocated with SDG::Malloc/SDG::Realloc
    void Free(void *block)
    {
        free(block);
    }
}
