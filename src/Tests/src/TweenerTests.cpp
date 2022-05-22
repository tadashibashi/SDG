#include "SDG_Tests.h"
#include <SDG/Math/Tweener.h>

TEST_CASE("Tweener tests", "[Tweener]")
{
    SECTION("Check default ctor values")
    {
        Tweener t;
        REQUIRE(!t.Paused());
        REQUIRE(t.Time() == 0);
        REQUIRE(t.Speed() == 1.f);
        REQUIRE(t.State() == Tweener::State::Standby);
    }

    SECTION("Check runtime values: non-yoyo")
    {
        float testVal = 0;
        Tweener t;
        t.Tween().Set(10.f, false, TweenF::Linear)
        .OnStep([&testVal](float val) {
            testVal = val * 10.f; // testVal set from 0 to 10.
        });

        SECTION("")
        {

        }
    }
}