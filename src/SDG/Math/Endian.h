//
//  Endian.h
//  SDG_Engine
//
//  Created by Aaron Ishibashi on 4/26/22.
//
#pragma once
#include <cstdint>
#include <cstddef>

namespace SDG
{
    enum class Endian : uint8_t
    {
        Unknown,
        Little,
        Big
    };

    /// Reverses the byte order of the type passed into it
    template <typename T>
    T ReverseEndian(T u)
    {
        union
        {
            T u;
            uint8_t u8[sizeof(T)];
        } source, dest;

        source.u = u;

        for (size_t k = 0; k < sizeof(T); k++)
            dest.u8[k] = source.u8[sizeof(T) - k - 1];

        return dest.u;
    }

    void *ReverseEndian(void *ptr, size_t size);

    /// Gets the endianness of the current operating system
    Endian SystemEndian();
}
