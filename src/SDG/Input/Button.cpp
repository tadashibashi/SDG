#include "Button.h"
#include <SDL_events.h>

namespace SDG
{
    const char *
    ButtonString(Button button)
    {
        return SDL_GameControllerGetStringForButton((SDL_GameControllerButton)button);
    }
}
