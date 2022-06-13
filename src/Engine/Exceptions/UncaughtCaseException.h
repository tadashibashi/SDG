#pragma once
#include "Exception.h"

namespace SDG
{
    /// Occurs when a case is unexpectedly defaulted in a switch-case block
    class UncaughtCaseException : public Exception
    {
    public:
        /// @param arg arbitrary arg to store in the Exception for the message.
        UncaughtCaseException(const String &message = String()) : Exception(message)
        { }

        const char *Name() const noexcept override { return "UncaughtCaseException"; }
    };
}
