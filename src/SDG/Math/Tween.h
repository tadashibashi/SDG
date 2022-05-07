#pragma once

#include <SDG/Math/TweenFunctions.h>
#include <functional>

namespace SDG
{
    class Tween
    {
    public:
        Tween(std::function<void(float)> setter, float start, float relVal,
              float duration, TweenFunction func);
        ~Tween() = default;

        /**
         * Sets the OnFinish callback
         * @param cb Callback to set
         * @return   this ref
         */
        Tween& OnFinish(std::function<void()> cb);

        /**
         * Sets the OnStep callback
         * @param cb  Callback to set
         * @return    this ref
         */
        Tween& OnStep(std::function<void(float)> cb);

        /**
         * Sets whether or not this Tween should have "yoyo" behavior.
         * @param setYoyo true sets yoyo behavior, false turns it off
         *                (default: false)
         * @return    this ref
         */
        Tween& SetYoyo(bool setYoyo);

        [[nodiscard]] bool IsYoyo() const {return isYoyo_;}

        /**
         * EmplaceTarget the currentTime to zero, and activate Tween
         */
        void Restart();
        void Restart(float startVal, float endVal, float duration,
                     TweenFunction func);
        void Start() { isActive_ = true;}
        void Stop(bool resetTween = true);

        /**
         * Change the setter to target other variables with this Tween.
         */
        void ChangeTarget(const std::function<void(float)>& setter);

        /**
         * Stops the Tween and sets its currentTime to 0
         */
        void Reset();

        /**
         * Stops the Tween, sets its currentTime to 0, and modifies essential Tween parameters
         */
        void Reset(float startVal, float endVal, float duration,
                   TweenFunction func);

        /**
         * EmplaceTarget the speed multiplier of the Tween (default: 1.f)
         * @param speed The value of speed to set
         */
        void SetSpeed(float speed) { speed_ = speed;}

        [[nodiscard]] float GetSpeed() const {return speed_;}

        /**
         * UpdateLastStates should be called every frame for accurate timing
         */
        void Update(float deltaTime); // end void evUpdate

    private:
        float currentTime_;
        float startVal_;
        float relVal_;
        float duration_;
        bool isActive_;
        bool isYoyo_;
        bool isReversing_;
        float speed_;

        // Callbacks

        // The Tween function to perform every call to evUpdate
        TweenFunction func_ = nullptr;

        // The function that alters the desired values
        std::function<void(float)> setter_;

        // The callback that sends when the Tween has reached the
        // destination
        std::function<void()> onFinish_;
        std::function<void(float)> onStep_;
    }; // end class Tween
}
