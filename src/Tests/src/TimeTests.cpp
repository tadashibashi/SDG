/* =============================================================================
 * TimeTests
 * 
 * 
 * ===========================================================================*/
#include "SDG_Tests.h"
#include <SDG/Time/Time.h>
#include <SDL.h>

TEST_CASE("Time tests", "[Time]")
{
    SECTION("Default constructor values")
    {
        Time time;
        REQUIRE(time.Ticks() == 0);
        REQUIRE(time.DeltaTicks() == 0);
    }

    SECTION("Regular use case")
    {
        // Initialize SDL, since Time depends on SDL
        REQUIRE(SDL_Init(SDL_INIT_TIMER) == 0);
        SDL_Delay(10);

        Time time;

        REQUIRE(time.Now() >= 10);
        time.Update();
        REQUIRE(time.Ticks() >= 10);

        SDL_Delay(10);
        time.Update();

        REQUIRE(time.DeltaTicks() >= 10);
        REQUIRE(time.Ticks() >= 20);

        double ms = time.As(Time::Unit::Milliseconds);
        REQUIRE(ms == (double)time.Ticks());
        REQUIRE(ms == time.As(Time::Unit::Seconds) * 1000.0);
        REQUIRE(ms == time.As(Time::Unit::Minutes) * 1000.0 * 60.0);
        REQUIRE(ms == time.As(Time::Unit::Hours) * 1000.0 * 3600.0);

        // test delta tick maxTicks feature
        SDL_Delay(70);
        time.Update();
        REQUIRE(time.DeltaTicks() == 64); // default max ticks value

        SDL_Delay(30);
        time.Update();
        REQUIRE(time.DeltaTicks(15) == 15);

        SDL_Delay(70);
        time.Update();
        REQUIRE(time.DeltaTicks(NULL) >= 70); // NULL removes cap

        SDL_Quit();
    }
}