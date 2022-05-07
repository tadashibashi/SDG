#include <SDG/Game.h>
#include <SDG/Platform.h>

/// To be defined by the user to return their own subclass.
SDG::Game *CreateGame();

static void mainLoop(void *arg)
{
    ((SDG::Game *)arg)->RunOneFrame();
}

int main(int argc, char *argv[])
{
    SDG::Game *game = CreateGame();

#if SDG_TARGET_WEBGL
    game->EmInitialize();
    emscripten_set_main_loop_arg(mainLoop, game, -1, true);
#else
    game->Run();
#endif
    delete game;
    return 0;
}