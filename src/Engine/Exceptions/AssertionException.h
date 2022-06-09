#pragma once
#include "Exception.h"

namespace SDG
{
    class AssertionException : public Exception
    {
    public:
        AssertionException(const String &statement, const char *file, int line, const char *func);
    };
}
