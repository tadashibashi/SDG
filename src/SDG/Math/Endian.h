//
//  Endian.h
//  SDG_Engine
//
//  Created by Aaron Ishibashi on 4/26/22.
//
#pragma once
#include <cstdint>

namespace SDG
{
    template <typename T>
    T ReverseEndian(T u)
    {
        union
        {
            T u;
            uint8_t u8[sizeof(T)];
        } source, dest;

        source.u = u;

        for (unsigned long k = 0; k < sizeof(T); k++)
            dest.u8[k] = source.u8[sizeof(T) - k - 1];

        return dest.u;
    }

    bool IsBigEndian()
    {
        static int isBigEndian = -1;
        if (isBigEndian == -1)
        {
            union {
                uint32_t word;
                uint8_t bytes[4];
            } test;
            test.word = 1u;

            isBigEndian = (test.bytes[0] == 0);
        }

        return isBigEndian;
    }
}
