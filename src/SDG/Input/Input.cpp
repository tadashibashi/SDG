//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Input.h"
#include <SDL_events.h>
#include "Keyboard.h"
#include "Mouse.h"
#include <SDG/Ref.h>

#include <vector>
#include <SDG/Debug/Assert.h>

using SDG::Key;

uint32_t SDG::Input::types;


static SDG::Keyboard keyboard;
static SDG::Mouse mouse;
static std::vector<SDG::Ref<SDG::InputComponent>> inputs;

void
SDG::Input::Initialize(uint32_t inputTypes)
{
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

    types = inputTypes;
}

void
SDG::Input::Close()
{
    for (Ref<InputComponent> input : inputs)
    {
        input->Close();
        types = 0;
    }
        
}

void
SDG::Input::UpdateLastStates()
{
    for (Ref<InputComponent> input : inputs)
    {
        input->UpdateLastStates();
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

void
SDG::Input::ProcessInput(void *evt)
{
    SDL_Event &ev = *static_cast<SDL_Event *>(evt);
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

SDG::CRef <SDG::Keyboard>
SDG::Input::Keyboard()
{
    return CRef{keyboard};
}

SDG::CRef <SDG::Mouse>
SDG::Input::Mouse()
{
    return CRef{mouse};
}
