//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Input.h"
#include <SDL_events.h>
#include <vector>
#include <cstdlib>
#include <cstring>

using std::vector;
using SDG::Key;

static Uint8 *lastKeyboardState;
static const Uint8 *currentKeyboardState;
static int numKeys = -1;

Uint8 KeyToScanCode(Key key)
{
    // TODO: Finish the keys in the KeyToScanCode function.
    switch (key)
    {
        case Key::A: return SDL_SCANCODE_A;
        case Key::B: return SDL_SCANCODE_B;
        case Key::C: return SDL_SCANCODE_C;
        case Key::D: return SDL_SCANCODE_D;
        case Key::E: return SDL_SCANCODE_E;
        case Key::F: return SDL_SCANCODE_F;
        case Key::G: return SDL_SCANCODE_G;
        case Key::H: return SDL_SCANCODE_H;
        case Key::I: return SDL_SCANCODE_I;
        case Key::J: return SDL_SCANCODE_J;
        case Key::K: return SDL_SCANCODE_K;
        case Key::L: return SDL_SCANCODE_L;
        case Key::M: return SDL_SCANCODE_M;
        case Key::N: return SDL_SCANCODE_N;
        case Key::O: return SDL_SCANCODE_O;
        case Key::P: return SDL_SCANCODE_P;
        case Key::Q: return SDL_SCANCODE_Q;
        case Key::R: return SDL_SCANCODE_R;
        case Key::S: return SDL_SCANCODE_S;
        case Key::T: return SDL_SCANCODE_T;
        case Key::U: return SDL_SCANCODE_U;
        case Key::V: return SDL_SCANCODE_V;
        case Key::W: return SDL_SCANCODE_W;
        case Key::X: return SDL_SCANCODE_X;
        case Key::Y: return SDL_SCANCODE_Y;
        case Key::Z: return SDL_SCANCODE_Z;


        case Key::Up: return SDL_SCANCODE_UP;
        case Key::Left: return SDL_SCANCODE_LEFT;
        case Key::Right: return SDL_SCANCODE_RIGHT;
        case Key::Down: return SDL_SCANCODE_DOWN;
        case Key::Return: return SDL_SCANCODE_RETURN;
        case Key::Space: return SDL_SCANCODE_SPACE;
        case Key::Escape: return SDL_SCANCODE_ESCAPE;

        default: return 0;
    }
}

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
SDG::Input::KeyPress(Key key)
{
    return static_cast<bool>(currentKeyboardState[KeyToScanCode(key)]);
}

bool
SDG::Input::KeyPressed(Key key)
{
    return static_cast<bool>(currentKeyboardState[KeyToScanCode(key)]) &&
        !static_cast<bool>(lastKeyboardState[KeyToScanCode(key)]);
}

bool
SDG::Input::KeyRelease(Key key)
{
    return !static_cast<bool>(currentKeyboardState[KeyToScanCode(key)]);
}

bool
SDG::Input::KeyReleased(Key key)
{
    return !static_cast<bool>(currentKeyboardState[KeyToScanCode(key)]) &&
            static_cast<bool>(lastKeyboardState[KeyToScanCode(key)]);
}