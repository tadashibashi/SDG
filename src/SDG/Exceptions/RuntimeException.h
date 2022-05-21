#pragma once
#include "Exception.h"

namespace SDG
{
    class RuntimeException : public Exception
    {
    public:
        /// @param message arbitrary arg to store in the Exception for the message.
        RuntimeException(const String &message) : Exception(message)
        { }

        /// Please override What() to specify the message
        RuntimeException() { }
    };
}
