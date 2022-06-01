/*!
 * @file Tween.h
 *
 * @class Tween
 * @abstract
 * A data class that describes an animation to be driven by a Tweener object.
 * Animated values are normalized from 0 to 1.
 *
 */
#pragma once
#include <SDG/Math/TweenFunctions.h>
#include <SDG/Lib/Ref.h>

#include <functional>

namespace SDG
{
    /// A data class that describes an animation to be driven by a Tweener object.
    /// Animated values are normalized from 0 to 1.
    class Tween
    {
        friend class Tweener;
    public:
        // ========== Constructors ==========
        /// Empty tween. Please make sure to call Set and set its values before
        /// attempting to use this Tween. TweenFunction is set to Linear.
        Tween();

        /// Creates a Tween that animates via a custom callback function.
        /// Values passed into the setter are normalized between 0 and 1.
        /// @param duration  time in seconds for this Tween to last.
        /// @param isYoyo    whether this Tween should reverse back once it reaches the end.
        /// @param func      a Tween function. Presets are located in the TweenF namespace.
        ///                  You can also create and use your own functions.
        /// @param setter    a custom callback that will receive the result of the Tween
        ///                  function on each call to Update.
        Tween(float duration, bool isYoyo, TweenFunction func,
              std::function<void(float)> setter);

        /// Creates a Tween that animates a float from 0 to 1.
        /// @param duration  time in seconds for this Tween to last.
        /// @param isYoyo    whether this Tween should reverse back once it reaches the end.
        /// @param func      a Tween function. Presets are located in the TweenF namespace.
        ///                  You can also create and use your own functions.
        /// @param ref       a reference to a float that will receive the result of the
        ///                  Tween function on each call to Update.
        Tween(float duration, bool isYoyo, TweenFunction func, Ref<float> ref);


        // ========== Setters / Getters ==========
        /// Sets Tween parameters, (but not callbacks).
        Tween &       Set(float duration, bool isYoyo, TweenFunction func);

        /// Set the callback function that will fire on Tween finish.
        Tween&        OnFinish(std::function<void()> cb);
        bool          HasFinishCallback() const { return (bool)onFinish_; }

        /// Set the callback function that will fire on each call to update.
        Tween &       OnStep(std::function<void(float)> setter);
        bool          HasStepCallback() const { return (bool)onStep_; }

        /// Get whether this Tween is set to yoyo-ing behavior.
        [[nodiscard]]
        bool          Yoyo() const {return isYoyo_;}

        /// Set whether this Tween has "yoyo-ing" behavior.
        Tween &       Yoyo(bool isYoyo);

        [[nodiscard]]
        float         Duration() const { return duration_; }
        Tween &       Duration(float duration);

        [[nodiscard]]
        TweenFunction Function() const { return func_; }
        Tween &       Function(TweenFunction func) { func_ = func; return *this; }


        /// Calculates the current value at a specified time.
        /// Will throw a NullReferenceException if TweenFunction was not set.
        /// @param seconds total time to calculate with.
        [[nodiscard]]
        float         CalculateValue(float seconds) const;

    private:
        // ========== Data members ==========
        float duration_;
        bool  isYoyo_;

        // ========== Callbacks ==========
        /// The Tween function to perform.
        TweenFunction              func_;

        /// Callback that fires on Update, which passes result of TweenFunction.
        std::function<void(float)> onStep_;

        /// Callback that fires when Tween has reached its destination.
        std::function<void()>      onFinish_;

    }; /* end class Tween */

} /* end namespace SDG */
