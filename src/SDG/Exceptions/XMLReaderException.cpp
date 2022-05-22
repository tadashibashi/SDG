#include "XMLReaderException.h"
#include <tinyxml2.h>
#include <ostream>

void
SDG::XMLReaderException::What(std::ostream &stream) const
{
    stream << "XMLReaderException occured while " << doing <<
    ": " << tinyxml2::XMLDocument::ErrorIDToName((tinyxml2::XMLError)error);
}
