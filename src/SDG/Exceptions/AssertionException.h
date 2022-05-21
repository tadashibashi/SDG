//
// Created by Aaron Ishibashi on 4/21/22.
//
#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    class AssertionException : public Exception
    {
    public:
        AssertionException(const String &statement, const char *file, int line, const char *func)
                : statement(statement), file(file), line(line), func(func)
        {}

    private:
        void What(std::ostream &stream) const override;
        String statement, file, func;
        int line;

    };
}