//
// Created by Aaron Ishibashi on 4/21/22.
//
#include "XMLReaderException.h"
#include <ostream>
#include <tinyxml2.h>

using namespace tinyxml2;

void
SDG::XMLReaderException::What(std::ostream &stream) const
{
    stream << "XMLReaderException occured while " << doing <<
    ": " << tinyxml2::XMLDocument::ErrorIDToName((XMLError)error);
}
