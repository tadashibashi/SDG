#pragma once
#include "Exception.h"

namespace SDG
{
    class XmlFormattingException : public Exception
    {
    public:
        XmlFormattingException(const String &message) : Exception(message) { }
    };
}