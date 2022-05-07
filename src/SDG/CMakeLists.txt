# [ SDG_Engine ] ====================================================
# ----- Sources -----------------------------------------------------
set(TinyXML2_Sources
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.h
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.cpp)

set(SDG_Engine_Sources
        ${TinyXML2_Sources}
        EntryPoint.cpp
        Graphics/Camera2D.cpp Graphics/Camera2D.h
        Graphics/GraphicsMgr.cpp Graphics/GraphicsMgr.h
        Graphics/Window.cpp Graphics/Window.h
        Graphics/RendererType.h
        "Graphics/Shader.cpp" "Graphics/Shader.h"
        Graphics/Color.h Graphics/Color.cpp
        "App.cpp" "App.h"
        "Platform.h"
        "Debug.hpp"
        "Debug/Logging.h"
        Debug/Logging.cpp
        Debug/Assert.h
        Debug/Assert.cpp
        "FileSys/FileSys.cpp" "FileSys/FileSys.h"
        FileSys/IO.cpp FileSys/IO.h
        FileSys/File.cpp Filesys/File.h
        "FileSys/XMLReader.cpp" "FileSys/XMLReader.h"
        "Scene.cpp" "Scene.h"
        "Input.hpp"
        "Input/Input.cpp" "Input/Input.h"
        "Input/Key.h"
        "Input/Keyboard.h" "Input/Keyboard.cpp"
        "Input/InputComponent.h"
        "AssetMgr.cpp" "AssetMgr.h"
        "Graphics/Texture2D.h" "Graphics/Texture2D.cpp"
        Math/Rand.cpp Math/Rand.h
        Math/Math.h
        Math.hpp
        Math/Vector2.h
        Exceptions/AssertionException.h
        Exceptions/XMLReaderException.h Exceptions/XMLReaderException.cpp
        Exceptions/AssertionException.cpp
        Templates/Delegate.h
        Math/Tween.cpp Math/Tween.h Math/TweenFunctions.cpp Math/TweenFunctions.h
        Graphics/SpriteBatch.cpp Graphics/SpriteBatch.h
        Math/Rectangle.h
        Math/Vector3.h
        FileSys/FileInfo.h Math/Endian.h FileSys.hpp FileSys/Structs/GameConfig.h
        SDG.hpp
        ServiceProvider.h Entities/Entity.cpp Entities/Entity.h Math/Matrix4x4.cpp Math/Matrix4x4.h GameTime.cpp GameTime.h Entities/ComponentList.cpp Entities/ComponentList.h Entities/Component.h Input/Mouse.cpp Input/Mouse.h Input/MButton.h Ref.h Exceptions/NullReferenceException.h Exceptions/NullReferenceException.cpp Graphics/RenderTarget.cpp Graphics/RenderTarget.h Math/Math.cpp ClassAttr.h Exceptions/InvalidArgumentException.cpp Exceptions/InvalidArgumentException.h)




# -----  Includes  ----------------------------------------------------
set(SDG_Engine_Includes
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/spdlog/include
        ${CMAKE_SOURCE_DIR}/lib/SDL/include
        ${CMAKE_SOURCE_DIR}/lib/sdl-gpu/include
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2
        ${CMAKE_SOURCE_DIR}/lib/glm)


# ----- Libraries ---------------------------------------------------
if (DEBUG)                                                 # Debug
    set(SDG_Engine_CompileDefs DEBUG=1)
    set(CONFIG_Libraries spdlog)
else()
    set(SDG_Engine_CompileDefs DEBUG=0)                    # Release
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
elseif(EMSCRIPTEN)                                         # HTML5
    set(CMAKE_CXX_FLAGS "-Os")
    set(CMAKE_EXE_LINKER_FLAGS "-sUSE_WEBGL2=1 -sWASM=2")

endif()

set (SDG_Engine_Libraries
        SDL2
        SDL2main
        SDL_gpu
        ${CONFIG_Libraries}
        ${PLATFORM_Libraries})




# ----- Commit the Settings ----------------------------------------
add_library                (SDG_Engine STATIC ${SDG_Engine_Sources})
target_include_directories (SDG_Engine PUBLIC ${SDG_Engine_Includes})
target_link_libraries      (SDG_Engine PUBLIC ${SDG_Engine_Libraries})
target_compile_definitions (SDG_Engine PUBLIC ${SDG_Engine_CompileDefs})
