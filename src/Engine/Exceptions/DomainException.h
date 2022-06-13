#pragma once
#include "Exception.h"

namespace SDG
{
    class DomainException : public Exception
    {
    public:
        DomainException(const String &message) : Exception(message)
        { }

        const char *Name() const noexcept override { return "DomainException"; }
    };
}
