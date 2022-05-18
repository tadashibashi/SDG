#include "Exception.h"
#include <string>
#include <sstream>

struct SDG::Exception::Impl
{
    std::string message;
};

SDG::Exception::Exception() : impl(new Impl) { }

SDG::Exception::Exception(const std::string &message) : impl(new Impl)
{
    impl->message = message;
}

SDG::Exception::~Exception() { delete impl; }

const char *SDG::Exception::what() const noexcept
{
    if (impl->message.empty())
    {
        std::stringstream stream;
        What(stream);
        impl->message = stream.str();
    }

    return impl->message.c_str();
}




