#pragma once
#include <Engine/Platform.h>
#include <SDL_gpu.h>

#if (SDG_TARGET_WEBGL) || (SDG_TARGET_ANDROID) || (SDG_TARGET_IPHONE)
    const GPU_RendererEnum RendererType = GPU_RENDERER_GLES_3;
#elif (SDG_TARGET_DESKTOP)
    const GPU_RendererEnum RendererType = GPU_RENDERER_OPENGL_3;
#endif
