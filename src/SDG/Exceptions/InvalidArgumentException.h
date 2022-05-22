#pragma once
#include "Exception.h"

namespace SDG
{
    class InvalidArgumentException : public Exception
    {
    public:
        InvalidArgumentException(const String &func, const String &arg,
                                 const String &info = String())  :
                func(func), arg(arg), info(info)
        { }

    private:
        void What(std::ostream &stream) const override;
        String func, arg, info;
    };
}
