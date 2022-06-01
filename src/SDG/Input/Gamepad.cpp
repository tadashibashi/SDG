#include "Gamepad.h"
#include <SDL_events.h>
#include <SDG/Lib/Memory.h>
#include <SDG/Debug/Log.h>

namespace SDG
{
    /// This array is used internally to convert an SDG::Button to its SDL counterpart.
    static SDL_GameControllerButton Buttons[(int8_t)Button::Max_];
    static Button SDGButtons[(int8_t)SDL_CONTROLLER_BUTTON_MAX];

    /// Used internally during Gamepad initialization to populate the Buttons array.
    static SDL_GameControllerButton SDGToSDLButton(Button button);
    static Button SDLButtonToSDG(Uint8 button);

    /// Checks if an SDL controller button is a button with an axis
    static bool IsAxisControl(Uint8 button);

    struct Gamepad::Impl
    {
        Impl(int index) :
            control(),
            buttons(Malloc<Sint16>((uint8_t)Button::Max_)),
            lastButtons(Malloc<Sint16>((uint8_t)Button::Max_)),
            index(index),
            id(-1),
            wasChanged(true)
        { }

        ~Impl()
        {
            Close();
            Free(buttons);
            Free(lastButtons);
        }

        bool IsOpen() const { return control; }
        void Close()
        {
            if (control)
            {
                SDL_GameControllerClose(control);
                control = nullptr;
                id = -1;
            }
        }

        SDL_GameController *control;
        Sint16 *buttons;
        Sint16 *lastButtons;
        int index;
        SDL_JoystickID id;
        bool wasChanged;
    };

    Gamepad::Gamepad(int index) : impl(new Impl(index))
    { }

    Gamepad::~Gamepad() { delete impl; }

    bool Gamepad::Press(Button button) const
    {
        return impl->buttons[(int8_t)button] != 0;
    }

    bool Gamepad::Release(Button button) const
    {
        return impl->buttons[(int8_t)button] == 0;
    }

    bool Gamepad::Pressed(Button button) const
    {
        return impl->buttons[(int8_t)button] != 0 &&
            impl->lastButtons[(int8_t)button] == 0;
    }

    bool Gamepad::Released(Button button) const
    {
        return impl->buttons[(int8_t)button] == 0 &&
            impl->lastButtons[(int8_t)button] != 0;
    }

    float Gamepad::Axis(Button button) const
    {
        float val = (float)impl->buttons[(int8_t)button];
        return (val > 0) ? val / SDL_MAX_SINT16 : -val / SDL_MIN_SINT16;
    }

    int Gamepad::Index() const
    {
        return impl->index;
    }

    bool Gamepad::IsOpen() const
    {
        return impl->IsOpen();
    }

    GamepadType Gamepad::Type() const
    {
        switch (SDL_GameControllerGetType(impl->control))
        {
        case SDL_CONTROLLER_TYPE_UNKNOWN: return GamepadType::Unknown;
        case SDL_CONTROLLER_TYPE_VIRTUAL: return GamepadType::Virtual;
        case SDL_CONTROLLER_TYPE_PS3: return GamepadType::PS3;
        case SDL_CONTROLLER_TYPE_PS4: return GamepadType::PS4;
        case SDL_CONTROLLER_TYPE_PS5: return GamepadType::PS5;
        case SDL_CONTROLLER_TYPE_XBOX360: return GamepadType::Xbox360;
        case SDL_CONTROLLER_TYPE_XBOXONE: return GamepadType::XboxOne;
        case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO: return GamepadType::SwitchPro;
        case SDL_CONTROLLER_TYPE_AMAZON_LUNA: return GamepadType::Luna;
        case SDL_CONTROLLER_TYPE_GOOGLE_STADIA: return GamepadType::Stadia;
        default:
            return GamepadType::Unknown;
        }
    }

    bool Gamepad::InitializeImpl()
    {
        Close();

        if (Buttons[(int8_t)Button::Left] != SDGToSDLButton(Button::Left))
        {
            for (int8_t i = 0; i < (int8_t)Button::Max_; ++i)
                Buttons[i] = SDGToSDLButton((Button)i);
        }

        if (SDGButtons[(Uint8)SDL_CONTROLLER_BUTTON_DPAD_UP] != SDLButtonToSDG(SDL_CONTROLLER_BUTTON_DPAD_UP))
        {
            for (Uint8 i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
                SDGButtons[i] = SDLButtonToSDG(i);
        }

        SDL_GameController *control = SDL_GameControllerOpen(impl->index);

        if (!control)
        {
            SDG_Core_Err("Failed to open Gamepad controller, index: {}: {}",
                impl->index, SDL_GetError());
            return false;
        }

        SDL_Joystick *joy = SDL_GameControllerGetJoystick(impl->control);
        if (!joy)
        {
            SDG_Core_Err("Failed to get Joystick from GameController: {}", SDL_GetError());
            SDL_GameControllerClose(control);
            return false;
        }

        SDL_JoystickID id = SDL_JoystickInstanceID(joy);
        if (id < 0)
        {
            SDG_Core_Err("Failed to get Joystick ID: {}", SDL_GetError());
            SDL_GameControllerClose(control);
            return false;
        }
        
        impl->control = control;
        impl->id = id;
        return true;
    }

    void Gamepad::ProcessInputImpl(const SDL_Event &ev)
    {
        if (!IsOpen()) return;

        // assumes that all events are GameController events
        switch (ev.type)
        {
        case SDL_CONTROLLERAXISMOTION:
            if (ev.caxis.which == impl->id)
            {
                impl->wasChanged = true;
                switch (ev.caxis.axis)
                {
                case SDL_CONTROLLER_AXIS_LEFTX:
                    impl->buttons[(int8_t)Button::LeftStickX] = ev.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_LEFTY:
                    impl->buttons[(int8_t)Button::LeftStickY] = ev.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTX:
                    impl->buttons[(int8_t)Button::RightStickX] = ev.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTY:
                    impl->buttons[(int8_t)Button::RightStickY] = ev.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                    impl->buttons[(int8_t)Button::LeftTrig] = ev.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                    impl->buttons[(int8_t)Button::RightTrig] = ev.caxis.value;
                    break;
                }
            }
            break;
        case SDL_CONTROLLERBUTTONUP:
            if (ev.cbutton.which == impl->id)
            {
                if (!IsAxisControl(ev.cbutton.button))
                {
                    impl->buttons[(int8_t)SDLButtonToSDG(ev.cbutton.button)] = 0;
                    impl->wasChanged = true;
                }  
            }
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            if (ev.cbutton.which == impl->id)
            {
                if (!IsAxisControl(ev.cbutton.button))
                {
                    impl->buttons[(int8_t)SDLButtonToSDG(ev.cbutton.button)] = 1;
                    impl->wasChanged = true;
                }
            }
            break;
        case SDL_CONTROLLERDEVICEADDED:
            if (ev.cdevice.which == impl->index)
            {
                Initialize();
                OnConnect.Invoke(impl->index);
            }
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            if (ev.cdevice.which == impl->id)
            {
                Close();
                OnRemove.Invoke(impl->index);
            }
            break;
        }
    }

    void Gamepad::UpdateLastStatesImpl()
    {
        if (impl->wasChanged)
        {
            memcpy(impl->lastButtons, impl->buttons, (int8_t)Button::Max_);
            impl->wasChanged = false;
        }
    }

    void Gamepad::CloseImpl()
    {
        impl->Close();
    }


    SDL_GameControllerButton SDGToSDLButton(Button button)
    {
        switch (button)
        {
        case Button::A: return SDL_CONTROLLER_BUTTON_A;
        case Button::B: return SDL_CONTROLLER_BUTTON_B;
        case Button::X: return SDL_CONTROLLER_BUTTON_X;
        case Button::Y: return SDL_CONTROLLER_BUTTON_Y;
        case Button::Back: return SDL_CONTROLLER_BUTTON_BACK;
        case Button::Guide: return SDL_CONTROLLER_BUTTON_GUIDE;
        case Button::Start: return SDL_CONTROLLER_BUTTON_START;
        case Button::LeftStickX: return SDL_CONTROLLER_BUTTON_LEFTSTICK;
        case Button::LeftStickY: return SDL_CONTROLLER_BUTTON_LEFTSTICK;
        case Button::RightStickX: return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
        case Button::RightStickY: return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
        case Button::LeftTrig: return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
        case Button::RightTrig: return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
        case Button::Up: return SDL_CONTROLLER_BUTTON_DPAD_UP;
        case Button::Down: return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
        case Button::Left: return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
        case Button::Right: return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
        case Button::Misc1: return SDL_CONTROLLER_BUTTON_MISC1;
        case Button::Paddle1: return SDL_CONTROLLER_BUTTON_PADDLE1;
        case Button::Paddle2: return SDL_CONTROLLER_BUTTON_PADDLE2;
        case Button::Paddle3: return SDL_CONTROLLER_BUTTON_PADDLE3;
        case Button::Paddle4: return SDL_CONTROLLER_BUTTON_PADDLE4;
        case Button::Touchpad: return SDL_CONTROLLER_BUTTON_TOUCHPAD;
        default:
            return SDL_CONTROLLER_BUTTON_INVALID;
        }
    }
    Button SDLButtonToSDG(Uint8 button)
    {
        switch (button)
        {
        case SDL_CONTROLLER_BUTTON_A: return Button::A;
        case SDL_CONTROLLER_BUTTON_B: return Button::B;
        case SDL_CONTROLLER_BUTTON_X: return Button::X;
        case SDL_CONTROLLER_BUTTON_Y: return Button::Y;
        case SDL_CONTROLLER_BUTTON_BACK: return Button::Back;
        case SDL_CONTROLLER_BUTTON_GUIDE: return Button::Guide;
        case SDL_CONTROLLER_BUTTON_START: return Button::Start;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK: return Button::LeftStickX;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK: return Button::RightStickX;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return Button::LeftTrig;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return Button::RightTrig;
        case SDL_CONTROLLER_BUTTON_DPAD_UP: return Button::Up;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return Button::Down;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return Button::Left;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return Button::Right;
        case SDL_CONTROLLER_BUTTON_MISC1: return Button::Misc1;
        case SDL_CONTROLLER_BUTTON_PADDLE1: return Button::Paddle1;
        case SDL_CONTROLLER_BUTTON_PADDLE2: return Button::Paddle2;
        case SDL_CONTROLLER_BUTTON_PADDLE3: return Button::Paddle3;
        case SDL_CONTROLLER_BUTTON_PADDLE4: return Button::Paddle4;
        case SDL_CONTROLLER_BUTTON_TOUCHPAD: return Button::Touchpad;
        default:
            return Button::Invalid;
        }
    }

    bool IsAxisControl(Uint8 button)
    {
        return button == SDL_CONTROLLER_BUTTON_LEFTSTICK || 
            button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER ||
            button == SDL_CONTROLLER_BUTTON_RIGHTSTICK || 
            button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    }
}


