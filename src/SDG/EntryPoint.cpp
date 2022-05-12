#ifndef SDG_NO_ENTRYPOINT
#include <SDG/App.h>

/// To be defined by the user in which they must return their own subclass of Game.
SDG::App *CreateApp();

int main(int argc, char *argv[])
{
    SDG::App *game = CreateApp();
    game->Run();

    delete game;
    return 0;
}

#endif
