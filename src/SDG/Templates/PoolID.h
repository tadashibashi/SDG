#pragma once
#include "Private/PoolNullIndex.h"
#include <cstdlib>

namespace SDG
{
    struct PoolID
    {
        PoolID() : index(PoolNullIndex), id(PoolNullIndex) {}
        PoolID(size_t index, size_t innerID) : index(index), id(innerID) {}
        size_t index;
        size_t id;
    };
}

