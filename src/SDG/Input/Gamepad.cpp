#include "Gamepad.h"
#include <SDL_events.h>
namespace SDG
{
    struct Gamepad::Impl
    {
        SDL_GameController *cont;
        
    };

    Gamepad::Gamepad() : impl()
    {
        SDL_ControllerButtonEvent ev;
        ev.button;
        SDL_GameControllerButton;
    }
}


