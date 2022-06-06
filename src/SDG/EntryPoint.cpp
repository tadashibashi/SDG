#ifndef SDG_NO_ENTRYPOINT
#include <SDG/App.h>
#include <SDG/Debug/Log.h>
#include <SDG/Exceptions/AssertionException.h>

using SDG::App;

/// To be defined by the user in which they must return their own subclass of Game.
App *CreateApp();

int main(int argc, char *argv[])
{
    App *app;
    try {
        app = CreateApp();
    }
    catch (const SDG::Exception &e)
    {
        SDG_Core_Err("Encountered SDG engine error during initialization: {}", e.what());
        exit(1);
    }
    catch (const std::exception &e)
    {
        SDG_Core_Err("Encountered standard library error during initialization: {}", e.what());
        exit(1);
    }
    catch (...)
    {
        SDG_Core_Err("Encountered an unknown error during initialization");
        exit(1);
    }

    try {
        app->Run();
        delete app;
    }
#if (SDG_DEBUG)
    catch (const SDG::AssertionException &e)
    {
        delete app;
        SDG_Core_Err("{} encountered assertion error during runtime: {}", app->Name(), e.what());
    }
#endif
    catch (const SDG::Exception &e)
    {
        delete app;
        SDG_Core_Err("{} encountered critical engine error during runtime: {}", app->Name(), e.what());
    }
    catch (const std::exception &e)
    {
        delete app;
        SDG_Core_Err("{} encountered standard library error during runtime: {}", app->Name(), e.what());
    }
    catch (...)
    {
        delete app;
        SDG_Core_Err("{} encountered an unknown error during runtime", app->Name());
    }

    return 0;
}

#endif
