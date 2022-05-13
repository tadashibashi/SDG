#pragma once
#include <exception>
#include <iosfwd>

namespace SDG
{
    class Exception : public std::exception
    {
        struct Impl;
    public:
        Exception();
        ~Exception();
        const char *what() const noexcept final;
    private:
        /// Subclasses will override this method and pass desired message to stream
        virtual void What(std::ostream &stream) const = 0;
        Impl *impl;
    };
}
