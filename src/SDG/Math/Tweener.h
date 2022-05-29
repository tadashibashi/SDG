/*!
 * @file Tweener.h
 * @namespace SDG
 * @class Tweener
 * Driver for a Tween. Designed to separate Tween data from runtime components.
 *
 */
#pragma once
#include "Tween.h"

namespace SDG
{
    /// Tween driver. Separates Tween data from runtime components.
    class Tweener
    {
    public:
        Tweener();

        /// Tweener playback states
        enum class State {
            /// Finished / waiting for call to Play()
            Standby,
            Starting,
            Stopping,
            /// Playing forward
            Forward,
            /// Reversing
            Backward
        };

        // ========== Driver ============

        /// Progresses the Tween. Drives the amount of time passed for the Tween.
        /// @param deltaSeconds time passed
        void Update(float deltaSeconds);

        // ========== Playback controls ==========

        /// Starts the Tweener. Behavior is like pressing a play button in audio software.
        /// Tween will restart if it was finished, and resume if it was paused_.
        /// Please use Restart for resetting the Tween.
        Tweener &Play();

        /// Immediately starts playback fresh from the beginning.
        Tweener &Restart();

        /// Stops the Tweener and resets the playback time to 0. Removes pause.
        Tweener &Stop();

        // ========== Getters / Setters =======================================

        /// Directly set the time.
        /// AppTime parameter automatically gets clamped between 0 and Tween's duration.
        Tweener &Time(float time);

        /// Gets the number of seconds progressed into the Tween.
        /// If Tweener is in forward mode, then time will be increasing until it
        /// reaches the Tween's duration.
        /// If Tweener is in backward mode, then time will be subtracting until it
        /// reaches zero.
        [[nodiscard]]
        float    Time() const;

        /// Set and modify the current Tween through this getter
        Tween &  Tween() { return tween; }

        /// Gets the Tweener's current playback state
        [[nodiscard]]
        enum State State() const { return state_; }

        /// Gets the current value calculated from the Tween during the last Update call.
        [[nodiscard]]
        float    CurrentValue() const { return currentValue; }

        /// Sets the current speed multiplier.
        /// Note: While negative values are allowed, it's currently untested.
        /// It's more efficient to set Paused(true), instead of setting Speed to 0.
        Tweener &Speed(float multiplier) { speed_ = multiplier; return *this; }

        /// Gets the current speed multiplier.
        [[nodiscard]]
        float    Speed() const { return speed_; }

        /// Sets whether the Tweener is paused_.
        Tweener &Paused(bool isPaused) { paused_ = isPaused; return *this; }

        /// Gets whether the Tweener is paused_.
        [[nodiscard]]
        bool     Paused() const { return paused_; }

    private:
        // ========== data members ==========

        float time_;
        bool paused_;
        float speed_;
        enum State state_;

        SDG::Tween tween;
        float currentValue; // cached to prevent repeat TweenFunction calls.

        // ========== helpers ==========

        void ApplyCurrentValue();
        void UpdateTimeCounter(float deltaSeconds);

        void ForwardState(float deltaSeconds);
        void BackwardState(float deltaSeconds);
        void Reset();
    };
}
