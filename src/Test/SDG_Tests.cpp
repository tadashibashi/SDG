#include <SDG/Game.h>
#include <SDG/Math.h>
#include "DelegateTests.h"

int main(int argc, char *argv[])
{

// TODO: It's kind of annoying to have to wrap code in try-catch block to use asserts.
// Perhaps default to logging to SDG_Err, and give the user the option to throw exception or not.
// Separate user Debug_Log for clients and SDG_Log functions for system.
try {
    SDG_Assert(SDG::Math::Lerp(0.0, 20.0, .5) == 10.0);
} catch(const SDG::AssertionException &e) {
    SDG_Log(e.what());
}
    TestDelegate();
    SDG::Game g;
    g.Run();
    return 0;
}

