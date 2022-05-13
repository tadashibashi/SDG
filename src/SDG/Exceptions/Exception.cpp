#include "Exception.h"
#include <string>
#include <sstream>

struct SDG::Exception::Impl
{
    std::string message;
};

SDG::Exception::Exception() : impl(new Impl) { }
SDG::Exception::~Exception() { delete impl; }
const char *SDG::Exception::what() const noexcept
{
    std::stringstream stream;
    What(stream);
    impl->message = stream.str();

    return impl->message.c_str();
}


