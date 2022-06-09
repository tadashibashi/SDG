#pragma once
#include "TimeUnit.h"

#include <cstdint>

namespace SDG
{
    /// Represents a duration of time
    class Duration
    {
    public:
        Duration(uint64_t sdlticks);
        Duration(long double time, TimeUnit units);
        Duration(uint64_t ms, uint64_t secs, uint64_t mins = 0, uint64_t hours = 0, uint64_t days = 0);

        // Retrieves total time in a particular unit
        double As(TimeUnit units) const;

        /// Retrieves the days portion of digital format DD:HH:MM:SS.MS
        uint16_t Days() const;

        /// Retrieves the hours portion of digital format DD:HH:MM:SS.MS
        uint16_t Hours() const;

        /// Retrieves the minutes portion of digital format DD:HH:MM:SS.MS
        uint16_t Minutes() const;

        /// Retrieves the seconds portion of digital format DD:HH:MM:SS.MS
        uint16_t Seconds() const;

        /// Retrieves the milliseconds portion of digital format DD:HH:MM:SS.MS
        uint16_t Milliseconds() const;

        /// Gets the raw total ticks (milliseconds)
        uint64_t Ticks() const { return ticks; }

        Duration &operator += (const Duration &other);
        Duration &operator -= (const Duration &other);
        Duration &operator *= (float scalar);
        Duration &operator /= (float scalar);
    private:
        uint64_t ticks;
    };

    Duration operator + (const Duration &a, const Duration &b);
    Duration operator - (const Duration &a, const Duration &b);
    Duration operator * (const Duration &a, float scalar);
    Duration operator / (const Duration &a, float scalar);
}
