#include "AssertionException.h"

#include <Engine/Filesys/Path.h>

SDG::AssertionException::AssertionException(const SDG::String &statement, const char *file, int line, const char *func)
    : Exception(String::Format("{}:{}:{}: {} assertion failed!", SDG::Path(file).Filename(), line, func, statement))
{ }