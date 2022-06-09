#pragma once
#include "TimeUnit.h"

#include <cstdint>

namespace SDG
{
    class Chronogram
    {
    public:
        Chronogram() : marker() { }

        /// Begin tracking time. App must be initialized before using.
        void Start();
        /// Get the time since Start was called
        double Check(TimeUnit units = TimeUnit::Milliseconds) const;
         
        /// Gets the time of the last call to Start
        double GetStartTime(TimeUnit units = TimeUnit::Milliseconds) const;
    private:
        uint64_t marker;
    };
}