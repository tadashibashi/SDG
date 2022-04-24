#include "Assert.h"

#if SDG_DEBUG
#include <SDG/Exceptions/AssertionException.h>
void
SDG::Debug::_AssertImpl(bool statement, const char *statementStr, const char *file, int line, const char *func)
{
    if (!statement)
    {
        throw SDG::AssertionException(statementStr, file, line, func);
    }
}

#endif