#include "CryptoTest.h"
#include <SDG/Game.h>
#include <SDG/Math.h>
#include "DelegateTests.h"

int main(int argc, char *argv[]) {
    SDG_Assert(SDG::Math::Lerp(0.0, 20.0, .5) == 10.0);
    CryptoTest();
    TestDelegate();
    SDG::Game g;
    g.Run();
    return 0;
}

