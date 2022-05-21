#include "Exception.h"
#include <string>
#include <sstream>

struct SDG::Exception::Impl
{
    SDG::String message;
};

SDG::Exception::Exception() : impl(new Impl) { }

SDG::Exception::Exception(const String &message) : impl(new Impl)
{
    impl->message = message;
}

SDG::Exception::~Exception() { delete impl; }

const char *SDG::Exception::what() const noexcept
{
    if (impl->message.Empty())
    {
        std::stringstream stream;
        What(stream);
        impl->message = stream.str();
    }

    return impl->message.Cstr();
}




