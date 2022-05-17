#include "Tweener.h"
#include "Math.h"

namespace SDG
{
    Tweener::Tweener() : currentSeconds(), state(State::Standby), paused(), speed(1.f),
        tween(), currentValue()
    {

    }

    void Tweener::Play()
    {
        // If Tween was left in a finished state, restart it
        if (this->state == State::Standby)
        {
            if (currentSeconds == tween.Duration())
                Restart();
            else
                state = State::Forward;
        }

        paused = false;
    }

    void Tweener::Stop()
    {
        currentSeconds = 0;
        state = State::Standby;
        paused = false;
    }

    void Tweener::Restart()
    {
        currentSeconds = 0;
        state = State::Forward;
        paused = false;
    }

    void Tweener::Update(float deltaSeconds)
    {
        if (paused)
            return;

        switch(state)
        {
            case State::Standby:
                break;
            case State::Forward: // actively moving forward
                currentValue = tween.CalculateValue(deltaSeconds);
                ApplyCurrentValue();
                UpdateTimeCounter(deltaSeconds);

                // State-leaving logic
                if (currentSeconds >= tween.Duration())
                {
                    if (tween.Yoyo())  // reverse Tween
                    {
                        state = State::Backward;
                        // Any time exceeding the duration gets reflected back
                        currentSeconds = tween.Duration() - (currentSeconds - tween.Duration());
                    }
                    else               // finished
                    {
                        state = State::Standby;
                        currentSeconds = tween.Duration(); // clamp time counter
                        if (tween.onFinish_)
                            tween.onFinish_();
                    }
                }
                break;
            case State::Backward: // actively yoyo-ing backward
                currentValue = tween.CalculateValue(deltaSeconds);
                ApplyCurrentValue();
                UpdateTimeCounter(deltaSeconds);

                // State-leaving logic
                if (currentSeconds <= 0) // finished
                {
                    // Just set to inactive and finish for now. May add ability to add
                    // repeating behavior later.
                    state = State::Standby;
                    currentSeconds = 0;
                    if (tween.onFinish_)
                        tween.onFinish_();
                }
                break;
        }
    }

    void Tweener::ApplyCurrentValue()
    {
        if (tween.onStep_)
            tween.onStep_(currentValue);
    }

    void Tweener::UpdateTimeCounter(float deltaSeconds)
    {
        // update time counter
        currentSeconds += deltaSeconds * speed *
                          ((state == State::Backward) ? -1.f : 1.f);
    }

    void Tweener::SetTime(float time)
    {
        currentSeconds = Math::Clamp<float>(time, 0, tween.duration_);
    }


}