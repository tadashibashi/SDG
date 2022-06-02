#ifndef SDG_NO_ENTRYPOINT
#include <SDG/App.h>

using SDG::App;

/// To be defined by the user in which they must return their own subclass of Game.
App *CreateApp();

int main(int argc, char *argv[])
{
    App *app = CreateApp();
    app->Run();

    delete app;

    return 0;
}

#endif
