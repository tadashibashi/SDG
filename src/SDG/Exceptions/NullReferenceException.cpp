#include "NullReferenceException.h"
#include <ostream>

void
SDG::NullReferenceException::What(std::ostream &os) const
{
    if (typeName.empty())
        os << "NullReferenceException";
    else
        os << "NullReferenceException with type \"" << typeName << "\"";
}
