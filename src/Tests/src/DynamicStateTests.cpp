#include "SDG_Tests.h"
#include <Engine/Logic/DynamicState.h>

static void DummyFunc(float time) { }

TEST_CASE("DynamicState tests", "[DynamicState]")
{
    DynamicState state;

    SECTION("Has* functions on default state")
    {
        REQUIRE(!state.HasStart());
        REQUIRE(!state.HasEnd());
        REQUIRE(!state.HasUpdate());
        REQUIRE(!state.HasPause());
        REQUIRE(!state.HasResume());
        REQUIRE(state.Empty());
    }

    SECTION("Set callback with lambda")
    {
        SECTION("Set OnStart")
        {
            state.OnStart([](float t) {});
            REQUIRE(state.HasStart());
        }

        SECTION("Set OnUpdate")
        {
            state.OnUpdate([](float t) {});
            REQUIRE(state.HasUpdate());
        }

        SECTION("Set OnEnd")
        {
            state.OnEnd([](float t) {});
            REQUIRE(state.HasEnd());
        }

        SECTION("Set OnPause")
        {
            state.OnPause([](float t) {});
            REQUIRE(state.HasPause());
        }

        SECTION("Set OnResume")
        {
            state.OnResume([](float t) {});

            REQUIRE(state.HasResume());
        }
    }

    SECTION("Set callback with global function")
    {
        SECTION("Set OnStart")
        {
            state.OnStart(DummyFunc);
            REQUIRE(state.HasStart());
        }

        SECTION("Set OnUpdate")
        {
            state.OnUpdate(DummyFunc);
            REQUIRE(state.HasUpdate());
        }

        SECTION("Set OnEnd")
        {
            state.OnEnd(DummyFunc);
            REQUIRE(state.HasEnd());
        }

        SECTION("Set OnPause")
        {
            state.OnPause(DummyFunc);
            REQUIRE(state.HasPause());
        }

        SECTION("Set OnResume")
        {
            state.OnResume(DummyFunc);
            REQUIRE(state.HasResume());
        }
    }
}
