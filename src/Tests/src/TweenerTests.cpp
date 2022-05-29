#include "SDG_Tests.h"
#include <SDG/Math/Tweener.h>
#include <SDG/Math/Math.h>

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

    SECTION("Check runtime values")
    {
        float testVal = 0;
        Tweener t;
        t.Tween().Set(10.f, false, TweenF::Linear)
        .OnStep([&testVal](float val) {
            testVal = Math::Lerp<float>(0, 10, val);
        });

        SECTION("Check values: non-yoyo")
        {
            REQUIRE(t.State() == Tweener::State::Standby);
            t.Play();
            REQUIRE(t.State() == Tweener::State::Forward);
            REQUIRE(testVal == 0);
            t.Update(5.0f);
            REQUIRE(testVal == 5);
            t.Update(2.5f);
            REQUIRE(testVal == 7.5f);
            t.Update(2.5f);
            REQUIRE(testVal == 10.f);
            REQUIRE(t.State() == Tweener::State::Standby);
        }

        SECTION("Check values: yoyo")
        {
            t.Tween().Yoyo(true);
            REQUIRE(t.State() == Tweener::State::Standby);
            t.Play();
            REQUIRE(t.State() == Tweener::State::Forward);
            REQUIRE(testVal == 0);
            t.Update(5.0f);
            REQUIRE(testVal == 5);
            t.Update(2.5f);
            REQUIRE(testVal == 7.5f);
            t.Update(2.5f);
            REQUIRE(testVal == 10.f);
            REQUIRE(t.State() == Tweener::State::Backward);
            t.Update(2.5f);
            REQUIRE(testVal == 7.5f);
            t.Update(2.5f);
            REQUIRE(testVal == 5.0f);
            t.Update(5.0f);
            REQUIRE(testVal == 0);
            REQUIRE(t.State() == Tweener::State::Standby);
        }

        SECTION("Pause prevents update seconds")
        {
            t.Play();
            t.Paused(true); // start Tweener in paused mode
            REQUIRE(t.Paused());
            t.Update(5.0f);
            REQUIRE(t.CurrentValue() == 0);
            REQUIRE(t.Time() == 0);
            REQUIRE(testVal == 0);

            // Now that it's unpaused, Tweener should update.
            t.Paused(false);
            REQUIRE(!t.Paused());
            t.Update(5.0f);
            REQUIRE(t.CurrentValue() == .5f);
            REQUIRE(t.Time() == 5.0f);
            REQUIRE(testVal == 5.0f);
        }
    }
}