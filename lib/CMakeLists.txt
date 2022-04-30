

add_subdirectory(SDL)

# For sdl-gpu's find SDL2
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SDL/include)

add_subdirectory(sdl-gpu)
add_subdirectory(spdlog)

# SDL_gpu needs defines set for WEBGL
if (WEBGL)
    set(GPU_CompileDefs
            SDL_GPU_DISABLE_OPENGL # use GLES3 by disabling
            SDL_GPU_DISABLE_GLES_2
            SDL_GPU_DISABLE_GLES_1
            MIN_WEBGL_VERSION=2    # use WEBGL 2
            MAX_WEBGL_VERSION=2)
    set_target_properties(SDL_gpu PROPERTIES
            COMPILE_DEFINITIONS "${GPU_CompileDefs}")
endif()
