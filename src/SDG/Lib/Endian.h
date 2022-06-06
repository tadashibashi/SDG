/*!
 * @file Endian.h
 * Contains utility functions pertaining to endianness
 */
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

    /// Reverses the byte order of a buffer of bytes
    void ReverseEndian(uint8_t *ptr, size_t size);

    /// Reverses the byte order of the type passed into it
    /// Please only use primitive types, since various compilers have
    /// implementation-specific ways of padding bytes in classes/structs.
    template <typename T>
    void ReverseEndian(T u)
    {
        ReverseEndian((uint8_t *)&u, sizeof(T));
    }

    /// Gets the endianness of the current operating system
    Endian SystemEndian();
}
