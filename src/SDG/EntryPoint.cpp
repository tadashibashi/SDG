#include <SDG/Game.h>

/// To be defined by the user to return their own subclass.
SDG::Game *CreateGame();

static SDG::Game *game;

static void mainLoop()
{
    game->RunOneFrame();
}

int main(int argc, char *argv[])
{
    game = new SDG::Game;

#if SDG_TARGET_WEBGL
    emscripten_set_main_loop(mainLoop, 0, true);
#else
    game->Run();
#endif
    delete game;
    return 0;
}