#include "OutOfRangeException.h"

SDG::OutOfRangeException::OutOfRangeException(int64_t value, const String &info) :
    LogicException(String::Format("OutOfRangeException: index [{}] was out of range", value)
        + (info.Empty() ? "" : ": " + info))
{ }

SDG::OutOfRangeException::OutOfRangeException(const String &info)
    :LogicException(info)
{
}
