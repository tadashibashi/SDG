#include "OutOfRangeException.h"
#include <ostream>

SDG::OutOfRangeException::OutOfRangeException(int64_t value, const String &info)
        : value(value), info(info)
{}

void SDG::OutOfRangeException::What(std::ostream &stream) const
{
    stream << "Out-of-range error with value " <<
           value << ": " << info;
}
