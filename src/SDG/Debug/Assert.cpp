/// Assert implementation file
#include "Assert.h"

#if SDG_DEBUG
#include "Log.h"

#include <SDG/Exceptions/AssertionException.h>
#include <SDG/FileSys/Path.h>

void
SDG::Debug::_AssertImpl(bool statement, const char *statementStr, const char *file, int line, const char *func,
                        bool shouldThrow)
{
    if (!statement)
    {
        if (shouldThrow)
            throw SDG::AssertionException(statementStr, file, line, func);
        else
        {
            SDG_Core_Warn("{}:{}: {}: Assertion failed: {}", Path(file).Filename(), line, func, statementStr);
        }

    }
}

#endif