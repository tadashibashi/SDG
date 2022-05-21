//
// Created by Aaron Ishibashi on 5/6/22.
//
#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    class NullReferenceException : public Exception
    {
    public:
        NullReferenceException() : message() { }
        explicit NullReferenceException(const String &message)
            : message(message) { }
    private:
        void What(std::ostream &stream) const override;
        String message;
    };
}
