#include "Endian.h"
#include <SDG/Exceptions/RuntimeException.h>
#include <cstdlib>
#include <cstring>

namespace SDG
{
    void ReverseEndian(uint8_t *ptr, size_t size)
    {
        uint8_t *temp = (uint8_t *)malloc(size);
        if (!temp)
            throw RuntimeException("ReverseEndian: failure during internal allocation: Out of memory");

        try
        {
            for (uint8_t *src = (uint8_t *)ptr, *target = temp + size - 1, *end = (uint8_t *)ptr + size;
                src != end;
                ++src, --target)
            {
                *target = *src;
            }
            memcpy(ptr, (void *)temp, size);
        }
        catch (const std::exception &e)
        {
            free(temp);
            throw e;
        }

        free(temp);
    }

    Endian SystemEndian()
    {
        static Endian endian = Endian::Unknown;
        if (endian == Endian::Unknown)
        {
            union {
                uint32_t word;
                uint8_t bytes[4];
            } test;
            test.word = 1u;

            endian = (test.bytes[0] == 0) ? Endian::Big : Endian::Little;
        }

        return endian;
    }
}