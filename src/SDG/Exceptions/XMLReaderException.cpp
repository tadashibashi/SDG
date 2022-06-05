#include "XMLReaderException.h"
#include <tinyxml2.h>

SDG::XMLReaderException::XMLReaderException(const String &doing, int error) :
    Exception(String::Format("XMLReaderException: task: {}: {}", doing, 
        tinyxml2::XMLDocument::ErrorIDToName((tinyxml2::XMLError)error)))
{ }
