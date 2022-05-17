/*!
 * @file Tweener.h
 * @abstract
 * Driver for a Tween. Designed to separate Tween data from runtime components.
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
            /// Playing forward
            Forward,
            /// Reversing
            Backward
        };

        // ========== Playback controls ==========

        /// Starts the Tweener. Behavior is like pressing a play button in audio software.
        /// Tween will restart if it was finished, and resume if it was paused.
        /// Please use Restart for resetting the Tween.
        void Play();

        /// Immediately starts playback fresh from the beginning.
        void Restart();

        /// Stops the Tweener and resets the playback time to 0. Removes pause.
        void Stop();

        /// Directly set the time.
        /// Time parameter automatically gets clamped between 0 and Tween's duration.
        void SetTime(float time);

        /// Progresses the Tween. Drives the amount of time passed for the Tween.
        /// @param deltaSeconds time passed
        void Update(float deltaSeconds);

        /// Gets the Tweener's current playback state
        State    PlaybackState() const { return state; }

        /// Set and modify the current Tween through this getter
        Tween &  CurrentTween() { return tween; }

        /// Gets the current value calculated from the Tween during the last Update call.
        [[nodiscard]]
        float    CurrentValue() const { return currentValue; }

        /// Sets the current speed multiplier.
        /// Note: While negative values are allowed, it's currently untested.
        /// It's more efficient to set Paused(true), instead of setting Speed to 0.
        Tweener &Speed(float multiplier) { speed = multiplier; return *this; }

        /// Gets the current speed multiplier.
        [[nodiscard]]
        float    Speed() const { return speed; }

        /// Sets whether the Tweener is paused.
        Tweener &Paused(bool isPaused) { paused = isPaused; return *this; }

        /// Gets whether the Tweener is paused.
        bool     Paused() const { return paused; }

    private:
        // ========== data members ==========
        float currentSeconds;
        bool paused;
        float speed;
        State state;

        Tween tween;
        float currentValue; // cached to prevent repeat TweenFunction calls.

        // ========== helpers ==========
        void ApplyCurrentValue();
        void UpdateTimeCounter(float deltaSeconds);
    };
}
