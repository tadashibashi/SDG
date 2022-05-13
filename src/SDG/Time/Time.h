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
    class  Time {
    public:
        Time();

        /// Should be called at the start of Game::UpdateLastStates()
        void Update();

        /// Returns the number of ticks passed since application start.
        /// This value is calculated at the start of this frame. A tick
        /// is a millisecond.
        [[nodiscard]] uint64_t Ticks() const { return ticks_; }

        /// Returns the number of ticks since last frame.
        /// Its max value is 64, to prevent physics problems.
        [[nodiscard]] int FrameTicks() const { return (int)deltaTicks_; }

        /// Returns the number of ticks at the moment this function is called.
        /// Use Ticks() to get the number of ticks passed since the beginning of
        /// this frame.
        [[nodiscard]] uint64_t Now() const;

    private:
        uint64_t ticks_;
        int8_t deltaTicks_;
    };
}
