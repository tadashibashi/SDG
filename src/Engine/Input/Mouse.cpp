//
// Created by Aaron Ishibashi on 5/5/22.
//
#include "Mouse.h"
#include <Engine/Debug/Log.h>
#include <SDL_events.h>

static const uint32_t mouseButtons[5] = {
    SDL_BUTTON_LMASK,
    SDL_BUTTON_RMASK,
    SDL_BUTTON_MMASK,
    SDL_BUTTON_X1MASK,
    SDL_BUTTON_X2MASK
};

namespace SDG
{
    Mouse::Mouse() : buttonMask(), lastButtonMask(),
        position(), lastPosition(), wheel(), lastWheel()
    { }

    Mouse::~Mouse()
    {

    }

    bool
    Mouse::InitializeImpl()
    {
        lastButtonMask = 0;
        buttonMask = 0;
        position = Point();
        lastPosition = Point();
        wheel = Vector2();
        lastWheel = Vector2();
        return true;
    }

    void
    Mouse::ProcessInputImpl(const SDL_Event &ev)
    {
        switch(ev.type)
        {
            case SDL_MOUSEWHEEL:
                wheel += Vector2(ev.wheel.preciseX, ev.wheel.preciseY);
                break;
        }
    }

    void
    Mouse::UpdateLastStatesImpl()
    {
        lastWheel = wheel;
        wheel = Vector2::Zero();
        lastButtonMask = buttonMask;
        lastPosition = position;

        int x, y;
        buttonMask = SDL_GetMouseState(&x, &y);
        position = {x, y};
    }

    void
    Mouse::CloseImpl()
    {
        lastButtonMask = 0;
        buttonMask = 0;
        position = Point();
        lastPosition = Point();
        wheel = Vector2();
        lastWheel = Vector2();
    }

    bool
    Mouse::Press(MButton button) const
    {
        return buttonMask & mouseButtons[(int)button];
    }

    bool
    Mouse::Pressed(MButton button) const
    {
        return (buttonMask & mouseButtons[(int)button]) &&
                !(lastButtonMask & mouseButtons[(int)button]);
    }

    bool
    Mouse::Release(MButton button) const
    {
        return !(buttonMask & mouseButtons[(int)button]);
    }

    bool
    Mouse::Released(MButton button) const
    {
        return !(buttonMask & mouseButtons[(int)button]) &&
               (lastButtonMask & mouseButtons[(int)button]);
    }
}
