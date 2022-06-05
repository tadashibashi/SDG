#include "Exception.h"
#include <SDG/Debug/Log.h>

SDG::Exception::Exception() : message() { }

SDG::Exception::Exception(const String &message) : message(message)
{
}

const char *SDG::Exception::what() const noexcept
{
    return message.Cstr();
}




