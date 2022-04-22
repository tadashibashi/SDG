//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Input.h"
#include <SDL_events.h>
#include "Keyboard.h"

using SDG::Key;


uint32_t SDG::Input::types = 0;


static SDG::Keyboard keyboard;

void
SDG::Input::Initialize(uint32_t inputTypes)
{
    types = inputTypes;
    keyboard.Initialize();
}

void
SDG::Input::Close()
{
    keyboard.Close();
}

void
SDG::Input::Update()
{
    keyboard.Update();
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
