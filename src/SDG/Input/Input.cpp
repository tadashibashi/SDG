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
SDG::Input::Update()
{
    keyboard.Update();
    mouse.Update();
}

bool
SDG::Input::KeyPress(Key key)
{
    return keyboard.IsKeyDown(key);
}

bool
SDG::Input::KeyPressed(Key key)
{
    return keyboard.JustPressed(key);
}

bool
SDG::Input::KeyRelease(Key key)
{
    return keyboard.IsKeyUp(key);
}

bool
SDG::Input::KeyReleased(Key key)
{
    return keyboard.JustReleased(key);
}

bool
SDG::Input::MousePress(MButton button)
{
    return mouse.ButtonPress(button);
}

bool
SDG::Input::MousePressed(MButton button)
{
    return mouse.ButtonPressed(button);
}

bool
SDG::Input::MouseRelease(MButton button)
{
    return mouse.ButtonRelease(button);
}

bool
SDG::Input::MouseReleased(MButton button)
{
    return mouse.ButtonReleased(button);
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

void SDG::Input::ProcessInput(void *evt)
{
    SDL_Event &ev = *static_cast<SDL_Event *>(evt);

    keyboard.ProcessInput(ev);
    if (ev.type == SDL_MOUSEWHEEL)
        mouse.ProcessInput(ev);
}

SDG::Vector2 SDG::Input::MouseWheel()
{
    return mouse.Wheel();
}

SDG::Vector2 SDG::Input::MouseLastWheel()
{
    return mouse.LastWheel();
}

bool SDG::Input::MouseWheelDidMove()
{
    return mouse.WheelDidMove();
}
