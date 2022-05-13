#include "InvalidArgumentException.h"
#include <ostream>

namespace SDG
{
    void
    InvalidArgumentException::What(std::ostream &stream) const
    {
        stream << "Invalid argument passed to " << func <<
        ". Arg name: " << arg;
        if (info)
            stream << ": " << info;
    }
}