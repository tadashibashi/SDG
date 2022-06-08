#include "OutOfRangeException.h"

SDG::OutOfRangeException::OutOfRangeException(int64_t value, const String &info) :
    RuntimeException(String::Format("OutOfRangeException: index [{}] was out of range", value)
        + (info.Empty() ? "" : ": " + info))
{ }
