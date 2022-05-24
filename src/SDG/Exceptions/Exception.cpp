#include "Exception.h"
#include <string>
#include <sstream>

SDG::Exception::Exception() : message() { }

SDG::Exception::Exception(const String &message) : message(message)
{
}

SDG::Exception::~Exception() { }

const char *SDG::Exception::what() const noexcept
{
    if (message.Empty())
    {
        std::stringstream stream;
        What(stream);
        message = stream.str();
    }

    return message.Cstr();
}




