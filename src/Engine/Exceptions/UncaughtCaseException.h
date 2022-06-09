#pragma once
#include "Exception.h"

namespace SDG
{
    class UncaughtCaseException : public Exception
    {
    public:
        /// @param arg arbitrary arg to store in the Exception for the message.
        UncaughtCaseException(const String &message = String()) : Exception(message)
        { }
    };
}
