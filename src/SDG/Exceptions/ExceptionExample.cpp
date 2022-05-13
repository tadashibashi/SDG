#include "ExceptionExample.h"
#include <ostream>

void
SDG::ExceptionExample::What(std::ostream &stream) const
{
    stream << "An exception occurred with argument: " << arg;
}
