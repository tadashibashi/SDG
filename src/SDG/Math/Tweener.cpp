#include "Tweener.h"
#include "Math.h"

namespace SDG
{
    Tweener::Tweener() : time_(), state_(State::Standby), paused_(),
                         speed_(1.f), tween(), currentValue()
    { }

    // ===== Playback controls ================================================

    Tweener &
    Tweener::Play()
    {
        // If Tween was left in a finished state, restart it
        if (state_ == State::Standby)
        {
            if (time_ == tween.Duration())
                Restart();
            else
                state_ = State::Forward;
        }

        paused_ = false;

        return *this;
    }

    Tweener &
    Tweener::Stop()
    {
        time_ = 0;
        state_ = State::Standby;
        paused_ = false;

        return *this;
    }

    Tweener &
    Tweener::Restart()
    {
        time_ = 0;
        state_ = State::Forward;
        paused_ = false;

        return *this;
    }

    // ===== Getters / Setters ================================================

    Tweener &
    Tweener::Time(float time)
    {
        time_ = Math::Clamp<float>(time, 0, tween.duration_);

        return *this;
    }

    float
    Tweener::Time() const
    {
        return time_;
    }

    // ===== Driver-related ===================================================

    void
    Tweener::Update(float deltaSeconds)
    {
        if (paused_)
            return;

        switch(state_)
        {
            case State::Standby: break;
            case State::Forward: ForwardState(deltaSeconds); break;
            case State::Backward: BackwardState(deltaSeconds); break;
        }
    }

    void
    Tweener::ForwardState(float deltaSeconds)
    {
        currentValue = tween.CalculateValue(deltaSeconds);
        ApplyCurrentValue();
        UpdateTimeCounter(deltaSeconds);

        // State-leaving logic
        if (time_ >= tween.Duration())
        {
            if (tween.Yoyo())  // reverse Tween
            {
                state_ = State::Backward;
                // Any time exceeding the duration gets reflected back
                time_ = tween.Duration() -
                        (time_ - tween.Duration());
            }
            else               // finished
            {
                state_ = State::Standby;
                time_ = tween.Duration(); // clamp time counter
                if (tween.onFinish_)
                    tween.onFinish_();
            }
        }
    }

    void
    Tweener::BackwardState(float deltaSeconds)
    {
        currentValue = tween.CalculateValue(deltaSeconds);
        ApplyCurrentValue();
        UpdateTimeCounter(-deltaSeconds);

        // State-leaving logic
        if (time_ <= 0) // finished
        {
            // Just set to inactive and finish for now.
            // May add ability to add repeating behavior later.
            state_ = State::Standby;
            time_ = 0;
            if (tween.onFinish_)
                tween.onFinish_();
        }
    }

    void
    Tweener::ApplyCurrentValue()
    {
        if (tween.onStep_)
            tween.onStep_(currentValue);
    }

    void
    Tweener::UpdateTimeCounter(float deltaSeconds)
    {
        // update time counter
        time_ += deltaSeconds * speed_ *
                 ((state_ == State::Backward) ? -1.f : 1.f);
    }

} /* end namespace SDG */
