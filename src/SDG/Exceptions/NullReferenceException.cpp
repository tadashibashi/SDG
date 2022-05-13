#include "NullReferenceException.h"
#include <ostream>

void
SDG::NullReferenceException::What(std::ostream &os) const
{
    if (typeName.empty())
        os << "Null reference error.";
    else
        os << "Null reference error of type " << typeName;
}
