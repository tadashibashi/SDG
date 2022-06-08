#pragma once
#include <string>

namespace SDG
{
    void ThrowRuntimeException(const std::string &message);
    void ThrowOutOfRangeException(int index, const std::string &message);
}
