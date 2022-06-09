#pragma once
#include <string>

namespace SDG
{
    void ThrowRuntimeException(const std::string &message = "");
    void ThrowOutOfRangeException(int index, const std::string &message = "");
    void ThrowNullReferenceException(const std::string &message = "");
    void ThrowInvalidArgumentException(const std::string &func, 
        const std::string &arg, const std::string &message = "");
}
