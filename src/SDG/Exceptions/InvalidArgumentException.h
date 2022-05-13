#pragma once
#include "Exception.h"

namespace SDG
{
    class InvalidArgumentException : public Exception
    {
    public:
        InvalidArgumentException(const char *func, const char *arg,
                                 const char *info = nullptr)  :
                func(func), arg(arg), info(info)
        { }

    private:
        void What(std::ostream &stream) const override;
        const char *func, *arg, *info;
    };
}
