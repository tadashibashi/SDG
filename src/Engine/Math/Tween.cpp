/// Tween implementation file
#include "Tween.h"
#include <Engine/Debug/Trace.h>
#include <Engine/Exceptions/InvalidArgumentException.h>
#include <Engine/Exceptions/NullReferenceException.h>

#include <utility>

namespace SDG
{
    Tween::Tween() :
            func_(TweenF::Linear), duration_(),
            onStep_(), isYoyo_()
    {}

    Tween::Tween(float duration, bool isYoyo, TweenFunction func,
                 std::function<void(float)> setter) :
            func_(func),
            isYoyo_(isYoyo),
            duration_(duration),
            onStep_(std::move(setter))
    {}

    Tween::Tween(float duration, bool isYoyo, TweenFunction func, Ref<float> ref)
            : duration_(duration), isYoyo_(isYoyo),
              func_(func), onStep_(
                    [&ref](float i)->void
                    {
                        *ref = i;
                    })
    {}

    // ===== Setters ==========================================================
    Tween&
    Tween::OnFinish(std::function<void()> cb)
    {
        onFinish_ = std::move(cb);
        return *this;
    }

    Tween &
    Tween::OnStep(std::function<void(float)> setter)
    {
        onStep_ = std::move(setter);
        return *this;
    }

    Tween &
    Tween::Set(float duration, bool isYoyo, TweenFunction func)
    {
        duration_ = duration;
        isYoyo_ = isYoyo;
        func_ = func;

        return *this;
    }

    Tween&
    Tween::Yoyo(bool isYoyo) {
        isYoyo_ = isYoyo;
        return *this;
    }

    float Tween::CalculateValue(float seconds) const
    {
        // Cannot calculate a value if there is no TweenFunction to perform.
        if (!func_)
            throw NullReferenceException(SDG_TRACE + ": Tween is missing "
                   "a TweenFunction");

        return func_(seconds, 0, 1.0f, duration_);
    }

    Tween &Tween::Duration(float duration)
    {
        if (duration < 0)
            throw InvalidArgumentException(__func__,
                   "duration", "duration must be >= 0");
        duration_ = duration;
        return *this;
    }

} /* end namespace SDG */
