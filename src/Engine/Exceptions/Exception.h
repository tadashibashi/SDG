#pragma once
#include <Engine/Lib/String.h>

#include <exception>
#include <iosfwd>

namespace SDG
{
    class Exception : public std::exception
    {
    public:
        /// Please override What() when using this constructor
        Exception();

        /// If this constructor is used, do not override What() or else this message
        /// will be overwritten.
        Exception(const String &message);
        virtual ~Exception() = default;
        const char *what() const noexcept;
    protected:
        mutable SDG::String message;
    };
}
