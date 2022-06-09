#pragma once
#include <Engine/Lib/Delegate.h>

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

        /// Sets the paused state. When paused is true, the effects of Update are ignored.
        void Paused(bool paused) { this->paused = paused; }

        void PauseToggle() { paused = !paused; }

        /// Gets the paused state. When paused, the effects of Update are ignored.
        [[nodiscard]] bool Paused() const { return paused; }

        /// Gets number of seconds left since the last call to Update.
        [[nodiscard]] float TimeLeft() const { return timeLeft; }

        /// Gets whether the state is actively counting down.
        [[nodiscard]] bool IsActive() const { return state == State::Countdown; }

        // ===== Events ========================================================

        /// Invoked when the time left reaches zero
        Delegate<void()> OnAlarm;
    private:
        enum class State : int8_t
        {
            Standby = 0,
            Countdown
        } state;

        float timeLeft;
        bool paused;
    };
}
