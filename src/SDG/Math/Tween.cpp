/**
 * Author: Aaron Ishibashi
 * Date: 3/18/2020
 *
 */
#include "Tween.h"
#include <SDG/Math/Math.h>
#include <utility>
#include <cmath>

namespace SDG
{
    Tween::Tween(float start, float end, float duration, TweenFunction func,
                 std::function<void(float)> setter) :
            currentTime_(),
            func_(func),
            startVal_(start),
            relVal_(end - start),
            duration_(duration),
            setter_(std::move(setter)),
            speed_(1.f),
            isYoyo_(false)
    {}

    // ===== Setters ==========================================================

    Tween&
    Tween::OnFinish(std::function<void()> cb)
    {
        onFinish_ = std::move(cb);
        return *this;
    }

    Tween&
    Tween::OnStep(std::function<void(float)> cb)
    {
        onStep_ = std::move(cb);
        return *this;
    }

    Tween&
    Tween::Yoyo(bool yoyo) {
        isYoyo_ = yoyo;
        return *this;
    }

    Tween &
    Tween::ChangeTarget(const std::function<void(float)> &setter)
    {
        setter_ = setter;
        return *this;
    }

    // ===== Playback Control =================================================

    Tween &
    Tween::Stop()
    {
        state = State::Inactive;
        Reset();

        return *this;
    }

    Tween &
    Tween::Reset()
    {
        currentTime_ = 0;
        state = State::Inactive;

        return *this;
    }

    Tween &
    Tween::Reset(float startVal, float endVal, float duration, TweenFunction func)
    {
        startVal_ = startVal;
        relVal_ = endVal - startVal_;
        duration_ = duration;
        func_ = func;

        Reset();

        return *this;
    }

    // ===== Runtime Impl ==========================================================

    void
    Tween::Update(const float deltaTime)
    {
        if (!paused_)
            return;

        switch(state)
        {
            case State::Inactive:
                break;
            case State::Forward: // actively moving forward
                ApplyCurrentValue();
                UpdateTimeCounter(deltaTime);

                // State-leaving logic
                if (currentTime_ >= duration_)
                {
                    if (isYoyo_)
                    {
                        state = State::Backward;
                        // any time exceeding the duration gets reflected back
                        currentTime_ = duration_ - (currentTime_ - duration_);
                    }
                    else
                    {
                        state = State::Inactive;
                        currentTime_ = duration_; // clamp time counter
                        if (onFinish_)
                            onFinish_();
                    }
                }
                break;
            case State::Backward: // actively yoyo-ing backward
                ApplyCurrentValue();
                UpdateTimeCounter(deltaTime);

                // State-leaving logic
                if (currentTime_ <= 0)
                {
                    // Just set to inactive and finish for now. May add ability to add
                    // multiple times to run Tween later.
                    state = State::Inactive;
                    currentTime_ = 0;
                    if (onFinish_)
                        onFinish_();
                }

                break;
        }
    }

    void Tween::ApplyCurrentValue()
    {
        // Make sure there is a function to calculate values by
        if (func_)
        {
            // calculate the current value
            float val = func_(currentTime_, startVal_, relVal_,
                              duration_);

            val = Math::Clamp<float>(val, startVal_, startVal_ + relVal_);

            // apply value to the setter function (if there is one)
            if (setter_) setter_(val);

            // fire step callback
            if (onStep_) onStep_(val);
        }
    }

    void Tween::UpdateTimeCounter(float deltaTime)
    {
        // update time counter
        currentTime_ += deltaTime * speed_ *
                        ((state == State::Backward) ? -1.f : 1.f);
    }
}