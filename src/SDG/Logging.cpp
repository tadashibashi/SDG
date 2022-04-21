//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "Logging.h"
#ifdef SDG_DEBUG
#include <spdlog/sinks/stdout_color_sinks.h>
#include <SDG/Exceptions/AssertionException.h>

static std::shared_ptr<spdlog::logger> Console;

spdlog::logger *
SDG::Logging::GetConsole()
{
    if (!Console.get())
        Console = spdlog::stdout_color_mt("SDG");
    return Console.get();
}

void
SDG::Logging::AssertImpl(bool statement, const std::string &statementStr, const char *file, int line, const char *func)
{
    if (!statement)
    {
        throw SDG::AssertionException(statementStr, file, line, func);
    }
}

#endif