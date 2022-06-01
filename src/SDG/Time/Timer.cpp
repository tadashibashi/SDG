#include "Timer.h"

SDG::Timer::Timer() : state(State::Standby), timeLeft(-1.f), paused(false)
{

}

// Drives the Timer countdown by deltaTime seconds. Intended to be called
// every frame, but this is not a necessity.
void SDG::Timer::Update(float deltaTime)
{
    if (paused) return;

    if (state == State::Countdown)
    {
        timeLeft -= deltaTime;

        if (timeLeft <= 0)
        {
            timeLeft = -1.f;
            state = State::Standby;
            OnAlarm.Invoke();
        }
    }
}

// ===== Controls =============================================================

// Set and start the timer 
void SDG::Timer::Start(float seconds) 
{ 
    timeLeft = seconds; 
    state = State::Countdown; 
    paused = false; 
}

// Stops the timer
void SDG::Timer::Stop() 
{ 
    timeLeft == -1.f; 
    state == State::Standby; 
    paused = false; 
}