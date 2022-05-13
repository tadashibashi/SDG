#include "AssertionException.h"
#include <ostream>

#include <SDG/FileSys/Path.h>

void SDG::AssertionException::What(std::ostream &stream) const
{
    stream << Path(file).Filename() << ":" << std::to_string(line) << ": "
        << func << ": \"" << statement << "\" assertion failed!";
}
