#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    /// Exception intended for indexers that have exceeded a container's bounds.
    class OutOfRangeException : public Exception
    {
    public:
        OutOfRangeException(int64_t value, const std::string &info);

    private:
        void What(std::ostream &stream) const override;

        int64_t value;
        std::string info;
    };
}
