//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once
#include "Key.h"
#include <cstdint>

namespace SDG
{
    enum InputTypes : uint32_t {
        SDG_INPUTTYPE_KEYBOARD = 1u,
        SDG_INPUTTYPE_MOUSE    = 1u << 1u,
        SDG_INPUTTYPE_GAMEPAD  = 1u << 2u
    };

    class Input {
    public:
        // Call this before the main loop begins
        static void Initialize(uint32_t types = SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_MOUSE);

        // Call this before the call to SDL_PollEvents
        static void Update();

        // Clean up, called when the app is shut down
        static void Close();

        static bool KeyPressed(Key key);
        static bool KeyPress(Key key);
        static bool KeyReleased(Key key);
        static bool KeyRelease(Key key);

    private:
        static uint32_t types;
    };
}
