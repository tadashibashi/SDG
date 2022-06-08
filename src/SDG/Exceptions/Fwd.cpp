#include "Fwd.h"
#include <SDG/Lib/String.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Exceptions/RuntimeException.h>
#include <SDG/Exceptions/NullReferenceException.h>
#include <SDG/Exceptions/InvalidArgumentException.h>

void SDG::ThrowOutOfRangeException(int index, const std::string &message)
{
    throw OutOfRangeException(index, message);
}

void SDG::ThrowRuntimeException(const std::string &message)
{
    throw RuntimeException(message);
}

void SDG::ThrowNullReferenceException(const std::string &message)
{
    throw NullReferenceException(message);
}

void SDG::ThrowInvalidArgumentException(const std::string &func, const std::string &arg, 
    const std::string &message)
{
    throw InvalidArgumentException(func, arg, message);
}
