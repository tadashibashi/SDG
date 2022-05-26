//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Platform.h>
#include <SDG/Ref.h>

#include <SDL_events.h>

#include <vector>


using SDG::Key;

uint32_t SDG::InputDriver::types;


static SDG::Keyboard keyboard;
static SDG::Mouse mouse;
static std::vector<SDG::Ref<SDG::InputComponent>> inputs;

uint32_t SDG::GetDefaultInputTypes()
{
#if (SDG_TARGET_DESKTOP)
    return SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_MOUSE | SDG_INPUTTYPE_GAMEPAD;
#elif (SDG_TARGET_MOBILE)
    return SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_TOUCH;
#elif (SDG_TARGET_WEB)
    return SDG_INPUTTYPE_KEYBOARD | SDG_INPUTTYPE_MOUSE | SDG_INPUTTYPE_GAMEPAD;
#endif
}

void
SDG::InputDriver::Initialize(uint32_t inputTypes)
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
SDG::InputDriver::Close()
{
    for (Ref<InputComponent> input : inputs)
    {
        input->Close();
        types = 0;
    }
        
}

void
SDG::InputDriver::UpdateLastStates()
{
    for (Ref<InputComponent> input : inputs)
    {
        input->UpdateLastStates();
    }
}

void
SDG::InputDriver::ProcessInput(const SDL_Event &ev)
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
SDG::Input::KeyPress(Key key)
{
    SDG_Assert(keyboard.WasInit());
    return keyboard.Press(key);
}

bool
SDG::Input::KeyPressed(Key key)
{
    SDG_Assert(keyboard.WasInit());
    return keyboard.Pressed(key);
}

bool
SDG::Input::KeyRelease(Key key)
{
    SDG_Assert(keyboard.WasInit());
    return keyboard.Release(key);
}

bool
SDG::Input::KeyReleased(Key key)
{
    SDG_Assert(keyboard.WasInit());
    return keyboard.Released(key);
}

bool
SDG::Input::MousePress(MButton button)
{
    SDG_Assert(mouse.WasInit());
    return mouse.Press(button);
}

bool
SDG::Input::MousePressed(MButton button)
{
    SDG_Assert(mouse.WasInit());
    return mouse.Pressed(button);
}

bool
SDG::Input::MouseRelease(MButton button)
{
    SDG_Assert(mouse.WasInit());
    return mouse.Release(button);
}

bool
SDG::Input::MouseReleased(MButton button)
{
    SDG_Assert(mouse.WasInit());
    return mouse.Released(button);
}

SDG::Point
SDG::Input::MousePosition()
{
    SDG_Assert(mouse.WasInit());
    return mouse.Position();
}

SDG::Point
SDG::Input::MouseLastPosition()
{
    SDG_Assert(mouse.WasInit());
    return mouse.LastPosition();
}

bool
SDG::Input::MouseDidMove()
{
    SDG_Assert(mouse.WasInit());
    return mouse.DidMove();
}

SDG::Vector2
SDG::Input::MouseWheel()
{
    return mouse.Wheel();
}

SDG::Vector2
SDG::Input::MouseLastWheel()
{
    return mouse.LastWheel();
}

bool
SDG::Input::MouseWheelDidMove()
{
    return mouse.WheelDidMove();
}
