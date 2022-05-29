#include "Button.h"
#include <SDL_events.h>

const char *
SDG::ButtonString(Button button)
{
    return SDL_GameControllerGetStringForButton((SDL_GameControllerButton)button);
}
