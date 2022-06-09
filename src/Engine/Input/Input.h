/*!
 * @file Input.h
 * @namespace SDG
 * @class Input
 * Static class to access input checks.
 * 
 */
#pragma once
#include "InputComponent.h"
#include "Key.h"
#include "MButton.h"

#include <Engine/Lib/Ref.h>
#include <Engine/Math/Vector2.h>

#include <cstdint>

namespace SDG
{
    enum InputType : uint32_t 
    {
        SDG_INPUTTYPE_DEFAULT  = 0,
        SDG_INPUTTYPE_KEYBOARD = 1u,
        SDG_INPUTTYPE_MOUSE    = 1u << 1u,
        SDG_INPUTTYPE_GAMEPAD  = 1u << 2u,
        SDG_INPUTTYPE_TOUCH    = 1u << 3u,
        SDG_INPUTTYPE_ALL      = 0xffffffff
    };

    uint32_t GetDefaultInputTypes();

    /// Static access to app input
    class Input 
    {
    public:
        static bool KeyPressed(Key key);
        static bool KeyPress(Key key);
        static bool KeyReleased(Key key);
        static bool KeyRelease(Key key);

        static bool MousePress(MButton button);
        static bool MousePressed(MButton button);
        static bool MouseRelease(MButton button);
        static bool MouseReleased(MButton button);
        static Point MousePosition();
        static Point MouseLastPosition();
        static bool MouseDidMove();
        static Vector2 MouseWheel();
        static Vector2 MouseLastWheel();
        static bool MouseWheelDidMove();
    };

    // For now, only available for App to control.
    class InputDriver
    {
        friend class Engine;
    public:
        InputDriver() = delete;
        ~InputDriver() = delete;
    private:
        // Call this before the main loop begins
        static void Initialize(uint32_t types = SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_MOUSE);

        // Call this before the call to SDL_PollEvents
        static void UpdateLastStates();

        static void ProcessInput(const union SDL_Event &ev);

        // Clean up, called when the app is shut down
        static void Close();
        static uint32_t types;
    };
}
