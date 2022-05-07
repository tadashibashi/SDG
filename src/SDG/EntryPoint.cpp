#include <SDG/Game.h>

/// To be defined by the user in which they must return their own subclass of Game.
SDG::Game *CreateGame();

int main(int argc, char *argv[])
{
    SDG::Game *game = CreateGame();
    game->Run();

    delete game;
    return 0;
}