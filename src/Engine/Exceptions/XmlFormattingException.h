#pragma once
#include "XmlException.h"

namespace SDG
{
    class XmlFormattingException : public XmlException
    {
    public:
        XmlFormattingException(const String &message) : XmlException(message) { }

        const char *Name() const noexcept override { return "XmlFormattingException"; }
    };
}
