# Add library subdirectories and apply definitions
if (NOT EMSCRIPTEN)
    add_subdirectory(SDL)
    add_subdirectory(SDL_ttf)
endif()

# For sdl-gpu's find SDL2
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)
set(SDL2_INCLUDE_DIR PATH ${CMAKE_SOURCE_DIR}/lib/SDL/include)

add_subdirectory(sdl-gpu)
add_subdirectory(spdlog)

# SDL_gpu needs defines set for WEBGL
if (WEBGL)
    set(GPU_CompileDefs
            SDL_GPU_DISABLE_OPENGL # use GLES3 by disabling the following...
            SDL_GPU_DISABLE_GLES_2
            SDL_GPU_DISABLE_GLES_1
            MIN_WEBGL_VERSION=2    # use WEBGL 2
            MAX_WEBGL_VERSION=2)
    set_target_properties(SDL_gpu PROPERTIES
            COMPILE_DEFINITIONS "${GPU_CompileDefs}")
endif()

if (MSVC)
    # In MSVC, if <cmath> is included after an SDL header, duplicate M_PI defines
    # occur. HAVE_M_PI set informs SDL2 to not provide an extra M_PI for us.
    set_property(TARGET SDL2 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS HAVE_M_PI)
endif()

add_subdirectory(crunch)
