//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Input.h"
#include <SDL_events.h>
#include "Keyboard.h"
#include "Mouse.h"


using SDG::Key;

uint32_t SDG::Input::types = 0;


static SDG::Keyboard keyboard;
static SDG::Mouse mouse;

void
SDG::Input::Initialize(uint32_t inputTypes)
{
    types = inputTypes;
    keyboard.Initialize();
    mouse.Initialize();
}

void
SDG::Input::Close()
{
    keyboard.Close();
    mouse.Close();
}

void
SDG::Input::UpdateLastStates()
{
    keyboard.UpdateLastStates();
    mouse.UpdateLastStates();
}

bool
SDG::Input::KeyPress(Key key)
{
    return keyboard.Press(key);
}

bool
SDG::Input::KeyPressed(Key key)
{
    return keyboard.Pressed(key);
}

bool
SDG::Input::KeyRelease(Key key)
{
    return keyboard.Release(key);
}

bool
SDG::Input::KeyReleased(Key key)
{
    return keyboard.Released(key);
}

bool
SDG::Input::MousePress(MButton button)
{
    return mouse.Press(button);
}

bool
SDG::Input::MousePressed(MButton button)
{
    return mouse.Pressed(button);
}

bool
SDG::Input::MouseRelease(MButton button)
{
    return mouse.Release(button);
}

bool
SDG::Input::MouseReleased(MButton button)
{
    return mouse.Released(button);
}

SDG::Point
SDG::Input::MousePosition()
{
    return mouse.Position();
}

SDG::Point
SDG::Input::MouseLastPosition()
{
    return mouse.LastPosition();
}

bool
SDG::Input::MouseDidMove()
{
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
            keyboard.ProcessInput(ev);
            break;
        case SDL_MOUSEWHEEL:
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
