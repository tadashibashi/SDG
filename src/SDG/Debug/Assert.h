/*!
 * @file Assert.h
 * Contains macros for assertions that run in debug mode only.
 * 
 */
#pragma once
#include <SDG/Lib/Platform.h>
#include <SDG/Exceptions/AssertionException.h> // for convenience
#include <SDG/Lib/String.h>

#if (SDG_DEBUG)

namespace SDG::Debug
{
    void _AssertImpl(bool statement, const char *statementStr, const char *file, int line, const char *func,
                     bool shouldThrow);
}


/// Throws an exception when statement is false
#define SDG_Assert(statement) (SDG::Debug::_AssertImpl(statement, #statement, __FILE__ , __LINE__, __func__, true))
/// Logs a warning to the console
#define SDG_AWarn(statement) (SDG::Debug::_AssertImpl(statement, #statement, __FILE__ , __LINE__, __func__, false))

#elif defined(MSVC)
#define SDG_Assert(statement) __noop
#define SDG_AWarn(statement) __noop
#else
#define SDG_Assert(statement)
#define SDG_AWarn(statement)
#endif