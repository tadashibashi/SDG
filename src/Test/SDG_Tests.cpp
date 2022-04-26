#include "CryptoTest.h"
#include <SDG/Platform.h>
#include <SDG/Game.h>
#include "DelegateTests.h"
#include <SDG/Math.h>

SDG::Game *game;

void mainLoop()
{
    game->RunOneFrame();
}

int main(int argc, char *argv[]) {

// TODO: It's kind of annoying to have to wrap code in try-catch block to use asserts.
// Perhaps default to logging to SDG_Err, and give the user the option to throw exception or not.
// Separate user Debug_Log for clients and SDG_Log functions for system.
try {
    SDG_Assert(SDG::Math::Lerp(0.0, 20.0, .5) == 10.0);
} catch(const SDG::AssertionException &e)
{
    SDG_Log(e.what());
}
    CryptoTest();
    TestDelegate();

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

