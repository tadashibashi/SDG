#include "InvalidArgumentException.h"

namespace SDG
{
    InvalidArgumentException::InvalidArgumentException(const String &func, const String &arg) : 
        LogicException(String::Format("InvalidArgumentException: in function: {}, arg: {}", func, arg))
    { }

    InvalidArgumentException::InvalidArgumentException(const String &func, const String &arg, 
        const String &info) :
        LogicException(String::Format("InvalidArgumentException: in function: {}, arg: {}:", 
            func, arg, info))
    { }
}
