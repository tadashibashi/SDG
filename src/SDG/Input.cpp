//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Input.h"
#include <SDL_events.h>
#include <vector>
#include <cstdlib>
#include <cstring>

using std::vector;

static Uint8 *lastKeyboardState;
static const Uint8 *currentKeyboardState;
static int numKeys = -1;

void
SDG::Input::Initialize()
{
    currentKeyboardState = SDL_GetKeyboardState(&numKeys);
    lastKeyboardState = (Uint8 *)malloc(numKeys);

    memcpy(lastKeyboardState, currentKeyboardState, numKeys);
}

void
SDG::Input::Close()
{
    free(lastKeyboardState);
    currentKeyboardState = nullptr;
    lastKeyboardState = nullptr;
}

void
SDG::Input::Update()
{
    memcpy(lastKeyboardState, currentKeyboardState, numKeys);
}

bool
SDG::Input::KeyPress(int key)
{
    return static_cast<bool>(currentKeyboardState[key]);
}

bool
SDG::Input::KeyPressed(int key)
{
    return static_cast<bool>(currentKeyboardState[key]) &&
        !static_cast<bool>(lastKeyboardState[key]);
}

bool
SDG::Input::KeyRelease(int key)
{
    return !static_cast<bool>(currentKeyboardState[key]);
}

bool
SDG::Input::KeyReleased(int key)
{
    return !static_cast<bool>(currentKeyboardState[key]) &&
            static_cast<bool>(lastKeyboardState[key]);
}