#pragma once
#include <exception>
#include <iosfwd>

namespace SDG
{
    class Exception : public std::exception
    {
        struct Impl;
    public:
        /// Please override What() when using this constructor
        Exception();

        /// If this constructor is used, do not override What() or else this message
        /// will be overwritten.
        Exception(const std::string &message);
        ~Exception();
        const char *what() const noexcept final;
    private:
        /// Subclasses will override this method and pass desired message to stream
        virtual void What(std::ostream &stream) const {};
        Impl *impl;
    };
}
