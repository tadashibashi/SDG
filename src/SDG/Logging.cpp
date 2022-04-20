//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "Logging.h"
#ifdef SDG_DEBUG
#include <spdlog/sinks/stdout_color_sinks.h>
static std::shared_ptr<spdlog::logger> Console;

spdlog::logger *GetConsole()
{
    if (!Console.get())
        Console = spdlog::stdout_color_mt("SDG");
    return Console.get();
}
#endif