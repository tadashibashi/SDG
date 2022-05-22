#include "Logging.h"

#if SDG_DEBUG
#include <spdlog/sinks/stdout_sinks.h>
#include <SDG/Exceptions/AssertionException.h>

static std::shared_ptr<spdlog::logger> Console;

spdlog::logger *
SDG::Debug::GetConsole()
{
    if (!Console.get())
        Console = spdlog::stdout_color_mt("SDG");
    return Console.get();
}

#endif