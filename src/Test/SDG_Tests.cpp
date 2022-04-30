#include <SDG/Platform.h>

#include <SDG/Game.h>
#include "DelegateTests.h"
#include <SDG/Math.h>

using namespace SDG;

class TestGame : public Game {
private:
    int Initialize() override
    {
        Game::Initialize();
        // Initialization logic here
        return 0;
    }

    void ProcessInput() override
    {

    }

    void Update() override
    {

    }

    void Render() override
    {

    }

    void Close() override
    {

    }

};

Game *CreateGame()
{
    return new TestGame;
}
