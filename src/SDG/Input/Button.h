/*!
 * @file Button.h
 * @namespace SDG
 * @enum Button
 * Controller button enumeration
 * 
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
        LeftStick,
        RightStick,
        LeftTrig,
        RightTrig,
        Up,          // d-pad Up
        Down,        // d-pad Down
        Left,        // d-pad Left
        Right,       // d-pad Right
        Misc,     // Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button
        Paddle1,  // Xbox Elite paddle P1
        Paddle2,  // Xbox Elite paddle P2
        Paddle3,  // Xbox Elite paddle P3
        Paddle4,  // Xbox Elite paddle P4
        Touchpad, // PS4/5 touchpad button
        Max_
    };

    const char *ButtonString(Button button);
}