//
// Created by Aaron Ishibashi on 4/21/22.
//
#include "XMLReaderException.h"
#include <tinyxml2.h>

using namespace tinyxml2;

SDG::XMLReaderException::XMLReaderException(const std::string &doing, int error)
{
    message = "XMLReaderException occurred while " + doing
              + ": ";
    message += XMLDocument::ErrorIDToName((XMLError)error);
}
