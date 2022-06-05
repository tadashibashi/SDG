#pragma once
#include "Exception.h"
#include <SDG/Lib/String.h>

namespace SDG
{
    /// Exception that throws when an XML reading error has occured
    class XMLReaderException : public Exception
    {
    public:
        /// @param doing The task that the program was doing when the error occured
        /// e.g. "opening file example.xml"
        /// @param error The tinyxml2 error code that occured.
        XMLReaderException(const String &doing, int error);
    };
}

