#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    class InvalidArgumentException : public Exception
    {
    public:
        InvalidArgumentException(const std::string &func, const std::string &arg,
                                 const std::string &info = std::string())  :
                func(func), arg(arg), info(info)
        { }

    private:
        void What(std::ostream &stream) const override;
        std::string func, arg, info;
    };
}
