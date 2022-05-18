#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    class RuntimeException : public Exception
    {
    public:
        /// @param message arbitrary arg to store in the Exception for the message.
        RuntimeException(const std::string &message) : Exception(message)
        { }

        /// Please override What() to specify the message
        RuntimeException() { }
    };
}
