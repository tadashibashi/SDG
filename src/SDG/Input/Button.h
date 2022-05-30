/*!
 * @file Button.h
 * @namespace SDG
 * @enum Button
 * Controller button enumeration
 */
#pragma once
#include <cstdint>

namespace SDG
{
    enum class Button : int8_t
    {
        Invalid = -1,
        A,
        B,
        X,
        Y,
        Back,
        Guide,
        Start,
        LeftStickX,  // Left stick horizontal axis (-1: full left; 0: no effect; 1: full right)
        LeftStickY,  // Left stick vertical axis (-1: full up; 0: no effect; 1: full down)
        RightStickX, // Right stick horizontal axis (-1: full left; 0: no effect; 1: full right)
        RightStickY, // Right stick vertical axis (-1: full up; 0: no effect; 1: full down)
        LeftTrig,
        RightTrig,
        Up,          // directional-pad: up
        Down,        // directional-pad: down
        Left,        // directional-pad: left
        Right,       // directional-pad: right
        Misc1,       // Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button
        Paddle1,     // Xbox Elite paddle P1
        Paddle2,     // Xbox Elite paddle P2
        Paddle3,     // Xbox Elite paddle P3
        Paddle4,     // Xbox Elite paddle P4
        Touchpad,    // PS4/5 touchpad button
        Max_         // number of Button enumerations
    };

    /// Get a string representation of a Button
    const char *ButtonString(Button button);
}