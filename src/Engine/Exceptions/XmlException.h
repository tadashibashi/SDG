#pragma once
#include "DomainException.h"

namespace SDG
{
    class XmlException : public DomainException
    {
    public:
        XmlException(const String &message) : DomainException(message) { }
        const char *Name() const noexcept override { return "XmlException"; }
    };
}
