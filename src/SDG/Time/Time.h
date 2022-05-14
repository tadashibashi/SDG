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
    public:
        enum class Unit
        {
            Ms,
            Sec,
            Min,
            Hr
        };

        Time();

        /// Should be called at the start of App::Update()
        void Update();

        /// Returns the number of ticks passed since application start.
        /// This value is calculated at the start of this frame. A tick
        /// is a millisecond.
        [[nodiscard]] uint64_t Ticks() const;

        /// Returns ticks calculated as a certain unit
        [[nodiscard]] double As(Unit unit);

        /// Returns the number of ticks since last frame.
        /// Its max value is 64, to prevent physics problems.
        [[nodiscard]] int FrameTicks() const { return (int)deltaTicks_; }

        /// Returns the number of ticks at the moment this function is called.
        /// Use Time() to get the number of ticks passed since the beginning of
        /// this frame.
        [[nodiscard]] uint64_t Now() const;

    private:
        uint64_t ticks_;
        int8_t deltaTicks_;
    };
}
