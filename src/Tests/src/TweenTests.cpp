#include "SDG_Tests.h"
#include <SDG/Math/Tween.h>
#include <SDG/Debug/Logging.h>

TEST_CASE("Tween tests", "[Tween]")
{
    SECTION("Constructors")
    {
        SECTION("Default")
        {
            Tween tween;
            REQUIRE(tween.Duration() == 0);
            REQUIRE(tween.Yoyo() == false);
            REQUIRE(tween.Function() == TweenF::Linear);
            REQUIRE(tween.HasStepCallback() == false);
            REQUIRE(tween.HasFinishCallback() == false);
        }

        SECTION("Param constructor with reference to value")
        {
            float val = 0;
            Tween tween(10, true, TweenF::EaseInCirc, Ref(val));
            REQUIRE(tween.Duration() == 10);
            REQUIRE(tween.Yoyo() == true);
            REQUIRE(tween.Function() == TweenF::EaseInCirc);
            REQUIRE(tween.HasStepCallback() == true);
            REQUIRE(tween.HasFinishCallback() == false);
        }

        SECTION("Param constructor with params, setter function")
        {
            float val = 0;
            std::function<void(float)> func = [&val](float v) { val = v; };
            Tween tween(10, true, TweenF::EaseInOutQuad, func);

            REQUIRE(tween.Duration() == 10);
            REQUIRE(tween.Yoyo() == true);
            REQUIRE(tween.Function() == TweenF::EaseInOutQuad);
            REQUIRE(tween.HasStepCallback() == true);
            REQUIRE(tween.HasFinishCallback() == false);
        }
    }
    SECTION("Missing tween function causes Tween::CalculateValue to throw")
    {
        Tween tween;
        tween.Function(nullptr);

        bool didThrow = false;
        try {
            float val = tween.CalculateValue(1.f);
            SDG_Core_Err("Failed to throw. Function returned: {}", val);
        }
        catch (const NullReferenceException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
    }
    SECTION("Set")
    {
        Tween tween;
        tween.Set(20.f, true, TweenF::EaseInBack);
        REQUIRE(tween.Duration() == 20.f);
        REQUIRE(tween.Yoyo() == true);
        REQUIRE(tween.Function() == TweenF::EaseInBack);
        REQUIRE(tween.HasStepCallback() == false);
        REQUIRE(tween.HasFinishCallback() == false);
    }
    SECTION("OnStep")
    {
        Tween tween;
        REQUIRE(tween.HasStepCallback() == false);
        tween.OnStep([](float i) {}); // dummy function
        REQUIRE(tween.HasStepCallback() == true);
    }
    SECTION("OnFinish")
    {
        Tween tween;
        REQUIRE(tween.HasFinishCallback() == false);
        tween.OnFinish([]() {}); // dummy function
        REQUIRE(tween.HasFinishCallback() == true);
    }
    SECTION("Individual setters")
    {
        Tween tween;
        tween
            .Duration(25.5f)
            .Yoyo(true)
            .Function(TweenF::EaseInExpo)
            .OnStep([](float i){})
            .OnFinish([](){});
        REQUIRE(tween.Duration() == 25.5f);
        REQUIRE(tween.Yoyo() == true);
        REQUIRE(tween.Function() == TweenF::EaseInExpo);
        REQUIRE(tween.HasStepCallback() == true);
        REQUIRE(tween.HasFinishCallback() == true);
    }
}