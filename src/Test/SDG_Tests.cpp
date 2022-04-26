<<<<<<< HEAD
#include <SDG/Platform.h>

=======
#include "CryptoTest.h"
#include <SDG/Platform.h>
>>>>>>> 70076c4 (Resolved conflicting changes)
#include <SDG/Game.h>
#include "DelegateTests.h"
#include <SDG/Math.h>

SDG::Game *game;

void mainLoop()
{
    game->RunOneFrame();
}

SDG::Game *game;

void mainLoop()
{
    game->RunOneFrame();
}
<<<<<<< HEAD

int main(int argc, char *argv[]) {
=======
    CryptoTest();
    TestDelegate();

>>>>>>> 70076c4 (Resolved conflicting changes)
    //SDG_Assert(SDG::Math::Lerp(0.0, 20.0, .5) == 10.0);
    //CryptoTest();
    //TestDelegate();
    game = new SDG::Game;
    if (!game)
    {
        SDG_Log("Error while initializing game!\n");
        return 1;
    }
#if SDG_TARGET_HTML5
    emscripten_set_main_loop(mainLoop, -1, true);
#else
    game->Run();
#endif

    return 0;
}
