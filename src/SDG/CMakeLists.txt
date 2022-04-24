# [ SDG_Engine ] ====================================================
# ----- Sources -----------------------------------------------------
set(SDG_Engine_Sources
        "Shader.cpp" "Shader.h"
        "Game.cpp" "Game.h"
        "Platform.h"
        "Logging.cpp" "Logging.h"
        "FileSys.cpp" "FileSys.h"
        "XMLReader.cpp" "XMLReader.h"
        "Scene.cpp" "Scene.h"
        "Input.h"
        "Input/Input.cpp" "Input/Input.h"
        "Input/Key.h"
        "Input/Keyboard.h" "Input/Keyboard.cpp"
        "Input/InputComponent.h"
        "ContentMgr.cpp" "ContentMgr.h"
        "Texture2D.h" "Texture2D.cpp"
        "Crypto.cpp" "Crypto.h"
        Math/Rand.cpp Math/Rand.h
        Math/Math.h
        Math.h
        Math/Vector2.h
        Exceptions/AssertionException.h
        Exceptions/XMLReaderException.h Exceptions/XMLReaderException.cpp
        Exceptions/AssertionException.cpp
        Events/Delegate.h
        Events.h)




# -----  Includes  ----------------------------------------------------
set(SDG_Engine_Includes
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/spdlog/include
        ${CMAKE_SOURCE_DIR}/lib/SDL/include
        ${CMAKE_SOURCE_DIR}/lib/sdl-gpu/include
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2)



# ----- Libraries ---------------------------------------------------
if (DEBUG)                                                 # Debug
    set(SDG_Engine_CompileDefs DEBUG=1)
    set(CONFIG_Libraries spdlog)
else()                                                     # Release
    set(CONFIG_Libraries)
endif()

if (APPLE)                                                 # Mac
    # Universal binary
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    set(PLATFORM_Libraries "-framework OpenGL")
elseif(WIN32)                                              # Windows
    set(PLATFORM_Libraries opengl32)
elseif(LINUX)
    set(PLATFORM_Libraries GL)
elseif(EMSCRIPTEN)                                         # HTML5 (Currently unsupported)
    message(Emscripten is currently unsupported.)
    set(CMAKE_CXX_FLAGS "-Os")
    set(CMAKE_EXE_LINKER_FLAGS "-sUSE_WEBGL2=1 -sWASM=2")
endif()

set (SDG_Engine_Libraries
        SDL2
        SDL2main
        SDL_gpu
        tinyxml2
        ${CONFIG_Libraries}
        ${PLATFORM_Libraries})




# ----- Commit the Settings ----------------------------------------
add_library                (SDG_Engine STATIC ${SDG_Engine_Sources})
target_include_directories (SDG_Engine PUBLIC ${SDG_Engine_Includes})
target_link_libraries      (SDG_Engine PUBLIC ${SDG_Engine_Libraries})
target_compile_definitions (SDG_Engine PUBLIC ${SDG_Engine_CompileDefs})
