#pragma once
#include <Engine/Lib/String.h>
#include <Engine/Debug/Log.h>
#include <Engine/Platform.h>

#include <fmod_studio.hpp>
#include <fmod_errors.h>

#if (SDG_DEBUG)
inline auto Check(FMOD_RESULT result, const char *message = nullptr) -> void
{
    if (result != FMOD_OK)
    {
        if (!message)
            SDG_Core_Err("FMOD Error: {}", FMOD_ErrorString(result));
        else
            SDG_Core_Err("FMOD Studio Error: problem while {}: {}", message, FMOD_ErrorString(result));
    }
}
#else
inline auto Check(FMOD_RESULT result, const char *message = nullptr) -> void
{

}
#endif
