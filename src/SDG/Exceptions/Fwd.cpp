#include "Fwd.h"
#include <SDG/Lib/String.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Exceptions/RuntimeException.h>

void SDG::ThrowOutOfRangeException(int index, const std::string &message)
{
    throw OutOfRangeException(index, message);
}

void SDG::ThrowRuntimeException(const std::string &message)
{
    throw RuntimeException(message);
}
