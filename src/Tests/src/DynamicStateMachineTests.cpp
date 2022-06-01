#include "SDG_Tests.h"
#include <SDG/Logic/DynamicStateMachine.h>

TEST_CASE("DynamicStateMachine tests", "[DynamicStateMachine]")
{
    DynamicStateMachine states;
    enum class State {
        Idle,
        Jump,
        Attack
    };

    SECTION("Drive Start, End, Update callbacks")
    {
        bool updated = false, started = false, ended = false;
        float updateTime = 0, startTime = 0, endTime = 0;
        states[State::Idle]
            .OnStart([&started, &startTime](float time) { started = true; startTime = time; })
            .OnEnd([&ended, &endTime](float time) { ended = true; endTime = time; })
            .OnUpdate([&updated, &updateTime](float time) { updated = true; updateTime = time; });

        states.Start(State::Idle);
        states.Update(5.f);
        states.EndCurrent();
        states.Update(5.f);

        REQUIRE(updated);
        REQUIRE(updateTime == 5.f);
        REQUIRE(started);
        REQUIRE(startTime == 0.f);
        REQUIRE(ended);
        REQUIRE(endTime == 5.f);
    }

    SECTION("Drive pause and resume callbacks")
    {
        bool paused = false, resumed = false;
        float pausedTime = 0, resumedTime = 0;
        states[State::Idle]
            .OnPause([&paused, &pausedTime](float time) { paused = true; pausedTime = time; })
            .OnResume([&resumed, &resumedTime](float time) { resumed = true; resumedTime = time; });
        states[State::Attack];
        states[State::Jump];

        states.Start(State::Idle);
        states.Update(1.f);
        states.Start(State::Attack, false);
        states.Update(1.f);
        REQUIRE(paused);
        REQUIRE(pausedTime == 1.f);
        states.EndCurrent();
        states.Update(1.f);
        REQUIRE(resumed);
        REQUIRE(resumedTime == 1.f);
    }
}