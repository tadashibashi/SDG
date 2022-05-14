/*!
 * @file    GameTime.h
 * @project SDG_Engine
 * @author  Aaron Ishibashi
 *
 * @class GameTime
 * @description This class tracks the total time passed since execution and
 * the time that has passed since last frame. It is owned by class Game.
 *
 */
#pragma once
#include <cstdint>

namespace SDG
{

    /// Class for tracking total time passed since execution and delta time.
    class  Time
    {
        static const unsigned DefaultMaxDeltaTicks = 64;
    public:
        enum class Unit
        {
            Milliseconds,
            Seconds,
            Minutes,
            Hours
        };

        Time();

        /// Intended to be called at the start of the app's update loop
        void Update();

        /// Returns the number of ticks passed since application start.
        /// This value is calculated at the start of this frame. A tick
        /// is a millisecond.
        [[nodiscard]] uint64_t Ticks() const;

        /// Returns ticks calculated in a specified unit
        /// Time stamped at the last call to Update
        [[nodiscard]] double As(Unit unit);

        /// Gets the number of ticks passed during the last Update period.
        /// @param cap optionally set max value to receive. This is
        /// a convenience feature in case physics receives too large a
        /// value during frame rate slow down.
        [[nodiscard]] uint64_t DeltaTicks(unsigned cap = DefaultMaxDeltaTicks) const;

        /// Returns the number of ticks at the moment this function is called.
        /// Use Time() to get the number of ticks passed since the beginning of
        /// this frame.
        [[nodiscard]] uint64_t Now() const;

    private:
        uint64_t ticks_, deltaTicks_;
    };
}
