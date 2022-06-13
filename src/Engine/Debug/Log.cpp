#include "Log.h"

#if (SDG_DEBUG)
#include <spdlog/sinks/stdout_color_sinks.h>

namespace SDG::Debug
{
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> clientLogger;

    spdlog::logger *
    CoreLogger()
    {
        if (!coreLogger.get())
        {
            coreLogger = spdlog::stdout_color_mt("SDG Engine");
            coreLogger->set_pattern("[%n][%^%l%$] %v");

            // for more on custom formatting: 
            // https://spdlog.docsforge.com/v1.x/3.custom-formatting/#pattern-flags
        }
            
        return coreLogger.get();
    }

    spdlog::logger *
    ClientLogger()
    {
        if (!clientLogger.get())
        {
            clientLogger = spdlog::stdout_color_mt("Client");
            clientLogger->set_pattern("[%n][%^%l%$] %v");
        }
            
        return clientLogger.get();
    }
}


#endif
