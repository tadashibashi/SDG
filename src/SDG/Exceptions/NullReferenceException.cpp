#include "NullReferenceException.h"
#include <ostream>

void
SDG::NullReferenceException::What(std::ostream &os) const
{
    if (message.empty())
        os << "NullReferenceException";
    else
        os << "NullReferenceException: " << message;
}
