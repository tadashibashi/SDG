#pragma once

#include <SDG/Math/TweenFunctions.h>
#include <functional>
#include <SDG/Ref.h>

namespace SDG
{
    class Tween
    {
    public:
        /// Creates a Tween that animates a value via a custom setter function
        Tween(float start, float end, float duration, TweenFunction func,
              std::function<void(float)> setter);

        /// Creates a Tween that animates a value.
        /// Note: all integral types will be floored. Setter uses floats.
        template <typename T>
        Tween(Ref<T> value, float start, float end, float duration, TweenFunction func)
            : startVal_(start), relVal_(end - start), duration_(duration), func_(func), setter_(
                [&value](float i)->void
                {
                    *value = (T)i;
                })
        {
            static_assert(std::is_arithmetic_v<T>,
                    "Value to be set must be an arithmetic type.");
        }

        enum class State {
            Inactive,
            Forward,
            Backward
        };

        /// Sets the OnFinish callback
        /// @param cb Callback to set
        /// @return   this ref
        Tween& OnFinish(std::function<void()> cb);

        /// Sets the OnStep callback
        /// @param cb  Callback to set
        /// @return    this ref
        Tween& OnStep(std::function<void(float)> cb);

        /// Sets whether this Tween has "yoyo-ing" behavior.
        /// @param yoyo true sets yoyo behavior, false turns it off
        /// (default: false)
        /// @return    this ref
        Tween& Yoyo(bool yoyo);


        /// Set the currentTime to zero, and activate Tween
        Tween &Restart();
        Tween &Restart(float startVal, float endVal, float duration,
                     TweenFunction func);
        Tween &Start() { paused_ = false; if (state == State::Inactive) Restart(); return *this; }
        Tween &Stop(bool resetTween = true);

        State CurrentState() const { return state; }


        /// Change the setter to target other variables with this Tween.
        Tween &ChangeTarget(const std::function<void(float)>& setter);


        /// Stops the Tween and sets its currentTime to 0
        Tween &Reset();

        /// Stops the Tween, sets its currentTime to 0, and modifies essential
        /// Tween parameters
        Tween &Reset(float startVal, float endVal, float duration,
                   TweenFunction func);


        /// Set the speed multiplier of the Tween (default: 1.f)
        /// @param speed multiplier value to set
        Tween &Speed(float speed) { speed_ = speed; return *this; }

        /// Gets the speed multiplier of the Tween.
        [[nodiscard]] float Speed() const {return speed_;}


        /// Intended to be called at the beginning of every frame for accurate
        /// time calculation. Refraining from calling this function effectively
        /// pauses the progression of the Tween.
        void Update(float deltaTime);

        [[nodiscard]] float Duration() const { return duration_; }
        Tween &Duration(float duration) { duration_ = duration; return *this; }
        [[nodiscard]] float StartVal() const { return startVal_; }
        Tween &StartVal(float startVal)  { startVal_ = startVal; return *this; }
        [[nodiscard]] float EndVal() const { return startVal_ + relVal_; }
        Tween &EndVal(float endVal)  { relVal_ = endVal - startVal_; return *this; }
        [[nodiscard]] bool Paused() const { return paused_; }
        Tween &Paused(bool paused) { paused_ = paused; return *this; }
        /// Get whether the Tween is currently in the reversing phase of the yoyo.
        [[nodiscard]] bool Reversing() const { return isYoyo_ && state == State::Backward; }
        /// Get whether this Tween is set to yoyo-ing behavior.
        [[nodiscard]] bool Yoyo() const {return isYoyo_;}
    private:
        float currentTime_, startVal_, relVal_, duration_, speed_;
        bool paused_, isYoyo_;

        // Callbacks

        // The Tween function to perform every call to evUpdate
        TweenFunction func_ = nullptr;

        // The function that alters the desired values
        std::function<void(float)> setter_;

        // The callback that sends when the Tween has reached the
        // destination
        std::function<void()> onFinish_;
        std::function<void(float)> onStep_;

        void ApplyCurrentValue();
        void UpdateTimeCounter(float deltaTime);

        State state {State::Inactive};
    }; // end class Tween
}
