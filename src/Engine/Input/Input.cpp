#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <Engine/Debug/Assert.h>
#include <Engine/Lib/Ref.h>
#include <Engine/Platform.h>

#include <SDL_events.h>

#include <vector>

namespace SDG
{
    uint32_t InputDriver::types;

    static Keyboard keyboard;
    static Mouse mouse;
    static std::vector<Ref<InputComponent>> inputs;

    uint32_t GetDefaultInputTypes()
    {
    #if (SDG_TARGET_DESKTOP)
        return SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_MOUSE | SDG_INPUTTYPE_GAMEPAD;
    #elif (SDG_TARGET_MOBILE)
        return SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_TOUCH;
    #elif (SDG_TARGET_WEBGL)
        return SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_MOUSE | SDG_INPUTTYPE_GAMEPAD;
    #else
        return 0;
    #endif
    }

    void
    InputDriver::Initialize(uint32_t inputTypes)
    {
        if (inputTypes == SDG_INPUTTYPE_DEFAULT)
            inputTypes = GetDefaultInputTypes();

        // Initialize input type if it has not yet been initialized
        if ((inputTypes & SDG_INPUTTYPE_KEYBOARD) && !(types & SDG_INPUTTYPE_KEYBOARD))
        {
            inputs.emplace_back(keyboard);
            keyboard.Initialize();
        }

        if ((inputTypes & SDG_INPUTTYPE_MOUSE) && !(types & SDG_INPUTTYPE_MOUSE))
        {
            inputs.emplace_back(mouse);
            mouse.Initialize();
        }

        // TODO: Gamepad class implementation

        types = inputTypes;
    }

    void
    InputDriver::Close()
    {
        for (Ref<InputComponent> input : inputs)
        {
            input->Close();
            types = 0;
        }
        
    }

    void
    InputDriver::UpdateLastStates()
    {
        for (Ref<InputComponent> input : inputs)
        {
            input->UpdateLastStates();
        }
    }

    void
    InputDriver::ProcessInput(const SDL_Event &ev)
    {
        switch (ev.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        case SDL_KEYMAPCHANGED:
            if (keyboard.WasInit())
                keyboard.ProcessInput(ev);
            break;
        case SDL_MOUSEWHEEL:
            if (mouse.WasInit())
                mouse.ProcessInput(ev);
            break;
        }
    }

    bool
    Input::KeyPress(Key key)
    {
        SDG_Assert(keyboard.WasInit());
        return keyboard.Press(key);
    }

    bool
    Input::KeyPressed(Key key)
    {
        SDG_Assert(keyboard.WasInit());
        return keyboard.Pressed(key);
    }

    bool
    Input::KeyRelease(Key key)
    {
        SDG_Assert(keyboard.WasInit());
        return keyboard.Release(key);
    }

    bool
    Input::KeyReleased(Key key)
    {
        SDG_Assert(keyboard.WasInit());
        return keyboard.Released(key);
    }

    bool
    Input::MousePress(MButton button)
    {
        SDG_Assert(mouse.WasInit());
        return mouse.Press(button);
    }

    bool
    Input::MousePressed(MButton button)
    {
        SDG_Assert(mouse.WasInit());
        return mouse.Pressed(button);
    }

    bool
    Input::MouseRelease(MButton button)
    {
        SDG_Assert(mouse.WasInit());
        return mouse.Release(button);
    }

    bool
    Input::MouseReleased(MButton button)
    {
        SDG_Assert(mouse.WasInit());
        return mouse.Released(button);
    }

    Point
    Input::MousePosition()
    {
        SDG_Assert(mouse.WasInit());
        return mouse.Position();
    }

    Point
    Input::MouseLastPosition()
    {
        SDG_Assert(mouse.WasInit());
        return mouse.LastPosition();
    }

    bool
    Input::MouseDidMove()
    {
        SDG_Assert(mouse.WasInit());
        return mouse.DidMove();
    }

    Vector2
    Input::MouseWheel()
    {
        return mouse.Wheel();
    }

    Vector2
    Input::MouseLastWheel()
    {
        return mouse.LastWheel();
    }

    bool
    Input::MouseWheelDidMove()
    {
        return mouse.WheelDidMove();
    }
}
