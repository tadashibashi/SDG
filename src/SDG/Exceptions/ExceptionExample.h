#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    class ExceptionExample : public Exception
    {
    public:
        /// @param arg arbitrary arg to store in the Exception for the message.
        ExceptionExample(const std::string &arg) : arg(arg)
        { }

    private:
        /// This function must be overriden, outputting the intended
        /// exception message to the stream.
        void What(std::ostream &stream) const override;
        std::string arg;
    };
}

