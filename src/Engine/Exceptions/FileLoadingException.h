#pragma once
#include "DomainException.h"

namespace SDG
{
    /// Thrown when a file fails to load
    class FileLoadingException : public DomainException
    {
    public:
        FileLoadingException(const String &filepath, const String &message = String()) : DomainException(
            String::Format("Failed to load file from \"{}\"{}"), 
            filepath, message.Empty() ? "" : ": " + message)
        { }

        const char *Name() const noexcept override { return "FileLoadingException"; }
    };
}
