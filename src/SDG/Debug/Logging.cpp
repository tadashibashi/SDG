#include "Logging.h"

#if (SDG_DEBUG)
#include <spdlog/sinks/stdout_color_sinks.h>

static std::shared_ptr<spdlog::logger> Console;

spdlog::logger *
SDG::Debug::CoreLogger()
{
    if (!Console.get())
        Console = spdlog::stdout_color_mt("SDG");
    return Console.get();
}

#endif