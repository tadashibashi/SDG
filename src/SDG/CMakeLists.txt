# [ SDG_engine ] ====================================================
# ----- Sources -----------------------------------------------------
set(SDG_Engine_SRCS
        "Shader.cpp"
        "Shader.h"
        "Game.cpp"
        "Game.h"
        "Platform.h"
        "Logging.cpp"
        "FileSys.cpp"
        "FileSys.h"
        "XMLReader.cpp"
        "XMLReader.h"
        "Scene.cpp"
        "Scene.h"
        "Input.h"
        "Input/Input.cpp"
        "Input/Input.h"
        "Input/Key.h"
        "Input/Keyboard.h"
        "Input/Keyboard.cpp"
        "Input/InputComponent.h"
        "ContentMgr.cpp"
        "ContentMgr.h"
        "Texture2D.h"
        "Texture2D.cpp"
        "Crypto.cpp"
        "Crypto.h"
        Math/Rand.cpp
        Math/Rand.h
        Math/Math.h
        Math.h
        Math/Vector2.h
        Exceptions/AssertionException.h
        Exceptions/XMLReaderException.h
        Exceptions/XMLReaderException.cpp
        Exceptions/AssertionException.cpp
        Events/Delegate.h
        Events.h
        Graphics.h)

add_library(SDG_Engine STATIC ${SDG_Engine_SRCS})


# -----  Includes  ----------------------------------------------------
target_include_directories(SDG_Engine PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/spdlog/include
        ${CMAKE_SOURCE_DIR}/lib/SDL/include
        ${CMAKE_SOURCE_DIR}/lib/sdl-gpu/include
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2)



# ----- Libraries ---------------------------------------------------
if (DEBUG)                                                 # Debug
    target_compile_definitions(SDG_Engine PUBLIC DEBUG=1)
    set(CONFIG_LIBS spdlog)
else()                                                     # Release
    set(CONFIG_LIBS)
endif()

if (APPLE)                                                 # Mac
    # Universal binary
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    set(PLATFORM_LIBS "-framework OpenGL")
elseif(WIN32)                                              # Windows
    set(PLATFORM_LIBS opengl32)
elseif(LINUX)
    set(PLATFORM_LIBS GL)
endif()

if (EMSCRIPTEN)
    # we don't need to add SDL2 because it is set in the em++ linker args

    set(CMAKE_CXX_FLAGS "-Os")
    set(CMAKE_EXE_LINKER_FLAGS "-sUSE_WEBGL2=1 -sWASM=2")
endif()

set (SDG_Engine_LIBS
        SDL2
        SDL2main
        SDL_gpu
        tinyxml2
        ${CONFIG_LIBS}
        ${PLATFORM_LIBS})

target_link_libraries(SDG_Engine PUBLIC ${SDG_Engine_LIBS})

add_dependencies(SDG_Engine SDG_ContentPipe)

# ----- Other Build Processes ----------------------------------------


