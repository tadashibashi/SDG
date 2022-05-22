/* =============================================================================
 * TimeTests
 * 
 * 
 * ===========================================================================*/
#include "SDG_Tests.h"
#include "SDG/Time/AppTime.h"
#include <SDL.h>

TEST_CASE("AppTime tests", "[AppTime]")
{
    SECTION("Default constructor values")
    {
        AppTime time;
        REQUIRE(time.Ticks() == 0);
        REQUIRE(time.DeltaTicks() == 0);
    }

    SECTION("Regular use case")
    {
        // Initialize SDL, since AppTime depends on SDL
        REQUIRE(SDL_Init(SDL_INIT_TIMER) == 0);
        SDL_Delay(10);

        AppTime time;

        REQUIRE(time.Now() >= 10);
        time.Update();
        REQUIRE(time.Ticks() >= 10);

        SDL_Delay(10);
        time.Update();

        REQUIRE(time.DeltaTicks() >= 10);
        REQUIRE(time.Ticks() >= 20);

        double ms = Round(time.As(TimeUnit::Milliseconds));
        REQUIRE(ms == (double)time.Ticks());
        REQUIRE(ms == Round(time.As(TimeUnit::Seconds) * 1000.0));
        REQUIRE(ms == Round(time.As(TimeUnit::Minutes) * 1000.0 * 60.0));
        REQUIRE(ms == Round(time.As(TimeUnit::Hours) * 1000.0 * 3600.0));

        // test delta tick maxTicks feature
        SDL_Delay(70);
        time.Update();
        REQUIRE(time.DeltaTicks() == 64); // default max ticks value

        SDL_Delay(30);
        time.Update();
        REQUIRE(time.DeltaTicks(15) == 15);

        SDL_Delay(70);
        time.Update();
        REQUIRE(time.DeltaTicks(0) >= 70); // NULL removes cap

        SDL_Quit();
    }
}