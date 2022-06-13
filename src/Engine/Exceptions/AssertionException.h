#pragma once
#include "Exception.h"

namespace SDG
{
    /// Thrown when an assertion fails to evaluate as true
    class AssertionException : public Exception
    {
    public:
        AssertionException(const String &statement, const char *file, int line, const char *func);
        const char *Name() const noexcept override { return "AssertionException"; }
    };
}
