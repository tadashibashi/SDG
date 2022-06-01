#pragma once
#include <SDG/Lib/Delegate.h>

namespace SDG
{
    class Timer
    {
    public:
        Timer();
    public:

        // ===== Driver =======================================================

        /// Drives the Timer countdown by deltaTime seconds. Intended to be 
        /// called every frame, but this is not a necessity.
        void Update(float deltaTime);

        // ===== Controls =====================================================

        /// Set and start the timer 
        void Start(float seconds);
        
        /// Stops the timer (pause set to false)
        void Stop();

        /// Sets the paused state
        void Paused(bool paused) { this->paused = paused; }

        // ===== Getters ======================================================

        /// Gets number of seconds left since the last call to Update.
        float TimeLeft() const { return timeLeft; }

        /// Gets the paused state.
        bool Paused() const { return paused; }

        /// Gets whether the state is actively counting down.
        bool IsActive() const { return state == State::Countdown; }

        // ===== Events ========================================================

        /// Invoked when the time left reaches zero
        Delegate<> OnAlarm;
    private:
        enum class State
        {
            Standby = 0,
            Countdown
        } state;

        float timeLeft;
        bool paused;
    };
}
