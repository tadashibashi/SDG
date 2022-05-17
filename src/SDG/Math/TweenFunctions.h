#pragma once

namespace SDG
{
    // TODO: Test TweenFunctions behavior compared to https://easings.net/

    // Type of function to transform a Tween
    // The parameters are: currentTime, start, relativeTarget, duration
    typedef float(*TweenFunction)(float, float, float, float);
    namespace TweenF
    {
        float Linear(float currentTime, float start, float relTarget, float duration);

        // Cubic
        float EaseInCubic(float currentTime, float start, float relTarget, float duration);
        float EaseOutCubic(float currentTime, float start, float relTarget, float duration);
        float EaseInOutCubic(float currentTime, float start, float relTarget, float duration);

        // Quad
        float EaseInQuad(float currentTime, float start, float relTarget, float duration);
        float EaseOutQuad(float currentTime, float start, float relTarget, float duration);
        float EaseInOutQuad(float currentTime, float start, float relTarget, float duration);

        // Quart
        float EaseInQuart(float currentTime, float start, float relTarget, float duration);
        float EaseOutQuart(float currentTime, float start, float relTarget, float duration);
        float EaseInOutQuart(float currentTime, float start, float relTarget, float duration);

        // Quint
        float EaseInQuint(float currentTime, float start, float relTarget, float duration);
        float EaseOutQuint(float currentTime, float start, float relTarget, float duration);
        float EaseInOutQuint(float currentTime, float start, float relTarget, float duration);

        // Sine
        float EaseInSine(float currentTime, float start, float relTarget, float duration);
        float EaseOutSine(float currentTime, float start, float relTarget, float duration);
        float EaseInOutSine(float currentTime, float start, float relTarget, float duration);

        // Back
        float EaseInBack(float currentTime, float start, float relTarget, float duration);
        float EaseOutBack(float currentTime, float start, float relTarget, float duration);
        float EaseInOutBack(float currentTime, float start, float relTarget, float duration);

        // Expo
        float EaseInExpo(float currentTime, float start, float relTarget, float duration);
        float EaseOutExpo(float currentTime, float start, float relTarget, float duration);
        float EaseInOutExpo(float currentTime, float start, float relTarget, float duration);

        // Circ
        float EaseInCirc(float currentTime, float start, float relTarget, float duration);
        float EaseOutCirc(float currentTime, float start, float relTarget, float duration);
        float EaseInOutCirc(float currentTime, float start, float relTarget, float duration);

        // Bounce
        float EaseInBounce(float currentTime, float start, float relTarget, float duration);
        float EaseOutBounce(float currentTime, float start, float relTarget, float duration);
        float EaseInOutBounce(float currentTime, float start, float relTarget, float duration);

    }
}
