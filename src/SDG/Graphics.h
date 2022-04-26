//
// Created by Aaron Ishibashi on 4/23/22.
//
#pragma once
#include <SDG/Platform.h>
#ifdef SDG_TARGET_HTML5
#define SDL_GPU_DISABLE_GLES_1 1
#define SDL_GPU_DISABLE_GLES_2 1
#define SDL_GPU_DISABLE_OPENGL 1
#include <GLES3/gl3.h>
#include <SDL_gpu.h>
#endif
