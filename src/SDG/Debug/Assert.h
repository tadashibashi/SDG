#pragma once
#include <SDG/Platform.h>
#include <SDG/Exceptions/AssertionException.h> // for convenience

#if SDG_DEBUG

namespace SDG::Debug
{
    void _AssertImpl(bool statement, const char *statementStr, const char *file, int line, const char *func);
}


#define SDG_Assert(statement) (SDG::Debug::_AssertImpl(statement, #statement, __FILE__ , __LINE__, __func__))
#else
#define SDG_Assert(statement)
#endif