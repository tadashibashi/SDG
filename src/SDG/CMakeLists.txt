# [ SDG_Engine ] ====================================================
# ----- Sources -----------------------------------------------------
set(TinyXML2_Sources
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.h
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.cpp)

set(Engine_Sources
        ${TinyXML2_Sources}
        SDG.hpp

        App.cpp App.h
        AssetMgr.cpp AssetMgr.h

        ClassMacros.h

        # Debug
        Debug.hpp
        Debug/Log.h
        Debug/Logging.cpp
        Debug/Assert.h
        Debug/Assert.cpp

        EntryPoint.cpp

        # Exceptions
        Exceptions/AssertionException.h Exceptions/AssertionException.cpp
        Exceptions/XMLReaderException.h Exceptions/XMLReaderException.cpp
        Exceptions/NullReferenceException.h Exceptions/NullReferenceException.cpp
        Exceptions/InvalidArgumentException.cpp Exceptions/InvalidArgumentException.h

        # FileSys
        FileSys.hpp
        FileSys/Structs/GameConfig.h
        FileSys/FileSys.cpp FileSys/FileSys.h
        FileSys/Private/IO.cpp FileSys/Private/IO.h
        FileSys/File.cpp Filesys/File.h
        FileSys/Path.cpp FileSys/Path.h
        FileSys/XMLReader.cpp FileSys/XMLReader.h

        Game/Entity.cpp Game/Entity.h
        Time/AppTime.cpp Time/AppTime.h
        Game/ComponentList.cpp Game/ComponentList.h Game/Component.h
        Game/Scene.cpp Game/Scene.h

        Graphics/Camera2D.cpp Graphics/Camera2D.h
        Graphics/WindowMgr.cpp Graphics/WindowMgr.h
        Graphics/Window.cpp Graphics/Window.h
        Graphics/Private/RendererType.h
        Graphics/Shader.cpp Graphics/Shader.h
        Graphics/Color.h Graphics/Color.cpp
        Graphics/SpriteBatch.cpp Graphics/SpriteBatch.h
        Graphics/Texture2D.h Graphics/Texture2D.cpp
        Graphics/Font.cpp Graphics/Font.h
        Graphics/RenderTarget.cpp Graphics/RenderTarget.h

        Input.hpp
        Input/Input.cpp Input/Input.h
        Input/Key.h
        Input/Keyboard.h Input/Keyboard.cpp
        Input/InputComponent.h
        Input/Mouse.cpp Input/Mouse.h Input/MButton.h

        Math/Rand.cpp Math/Rand.h
        Math/Math.h
        Math.hpp
        Math/Vector2.h
        Math/Tween.cpp Math/Tween.h Math/TweenFunctions.cpp Math/TweenFunctions.h
        Math/Endian.h
        Math/Matrix4x4.cpp Math/Matrix4x4.h
        Math/Rectangle.h
        Math/Vector3.h
        Math/Math.cpp

        Platform.h

        Ref.h

        ServiceProvider.h

        Templates/Delegate.h
        Exceptions.hpp Exceptions/Exception.h 
        Exceptions/Exception.cpp Exceptions/ExceptionExample.h 
        Exceptions/ExceptionExample.cpp 
        Templates/Pool.h 
        Math/MathConstants.h 
        Exceptions/OutOfRangeException.h 
        Exceptions/OutOfRangeException.cpp 
        Unique.h 
        Graphics/Flip.h 
        Graphics/Flip.cpp 
        Graphics/Private/TranslateFlip.h Graphics/Private/TranslateFlip.cpp 
        Math/Private/Conversions.h Graphics/Private/Conversions.h 
        Math/Tweener.cpp Math/Tweener.h 
        Debug/Trace.h 
        Exceptions/RuntimeException.h 
        Templates/PoolID.h 
        Templates/Private/PoolNullIndex.h 
        Templates/Private/PoolNullIndex.cpp 
        Templates/FixedPool.h
        String.h String.cpp
        Time/TimeUnit.h Debug/LogImpl.h Templates/Swap.h Math/MathShape.h Math/MathShape.cpp Math/Intersection.h Math/Circle.h "StringView.h" "StringView.cpp" "Buffer.cpp" "Buffer.h" Math/Endian.cpp "Memory.h" "Position.h" Graphics/Sprite.h Graphics/Frame.h Exceptions/DivisionByZeroException.h)

# -----  Includes  ----------------------------------------------------
set(Engine_Includes
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/spdlog/include
        ${CMAKE_SOURCE_DIR}/lib/SDL/include
        ${CMAKE_SOURCE_DIR}/lib/sdl-gpu/include
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2
        ${CMAKE_SOURCE_DIR}/lib/glm
        ${CMAKE_SOURCE_DIR}/lib/bundled/include)



# ----- Libraries ---------------------------------------------------
if (DEBUG)                                                 # Debug
    set(Engine_CompileDefs DEBUG=1)
    set(CONFIG_Libraries spdlog)
    if (WIN32)
        if ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
            set(CONFIG_Libraries ${CONFIG_Libraries} SDL2 SDL2main)
        else()
            set(CONFIG_Libraries ${CONFIG_Libraries} SDL2d SDL2maind)
        endif()
    else()
        set(CONFIG_Libraries ${CONFIG_Libraries} SDL2)
    endif()
else()
    set(Engine_CompileDefs DEBUG=0)                        # Release
    if (WIN32)
        set(CONFIG_Libraries SDL2 SDL2main)
    else()
        set(CONFIG_Libraries SDL2)
    endif()
endif()

if     (APPLE)                                              # Mac
    # Universal binary
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    set(PLATFORM_Libraries "-framework OpenGL" "-framework Cocoa")

elseif (WIN32)                                              # Windows
    set(PLATFORM_Libraries opengl32)

elseif (LINUX)                                              # Linux
    set(PLATFORM_Libraries GL)

elseif (EMSCRIPTEN)                                         # HTML5
    set(CMAKE_CXX_FLAGS "-Os -sUSE_SDL=2 -sUSE_SDL_TTF=2")
    set(CMAKE_EXE_LINKER_FLAGS "-sUSE_WEBGL2=1 -sWASM=2")
endif()


# ----- Bundled Libraries ----------------------------------------
if (WINDOWS)   # for Windows
    if (DEBUG AND NOT "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo") # set the prefix path for bundled libraries
        set(BundledPref "${CMAKE_SOURCE_DIR}/lib/bundled/win/debug")
    else()
        set(BundledPref "${CMAKE_SOURCE_DIR}/lib/bundled/win/release")
    endif()
    # Set paths to the bundled libs
    set(Engine_BundledLibs "${BundledPref}/SDL2_ttf.lib")

    # Copy bundeled dlls to the build directory
    file(GLOB_RECURSE WindowsDlls ${BundledPref}/*.dll)
    foreach(dll ${WindowsDlls})
        get_filename_component(DllName ${dll} NAME)
        configure_file(${dll} ${CMAKE_BINARY_DIR}/${DllName} COPYONLY)
    endforeach()
elseif(APPLE)  # for Mac
    set(BundledPref "${CMAKE_SOURCE_DIR}/lib/bundled/macos")
    set(Engine_BundledLibs "${BundledPref}/libSDL2_ttf.a")
elseif(LINUX)  # for Linux
    set(Engine_BundledLibs "${CMAKE_SOURCE_DIR}/lib/bundled/linux")
else()
    set(Engine_BundledLibs)
endif()

set (Engine_Libraries
        ${Engine_BundledLibs}
        ${CONFIG_Libraries}
        ${PLATFORM_Libraries}
        SDL_gpu)


# ----- Commit the Settings ----------------------------------------
add_library                (SDG_Engine STATIC ${Engine_Sources})
target_include_directories (SDG_Engine PUBLIC ${Engine_Includes})
target_link_libraries      (SDG_Engine PUBLIC ${Engine_Libraries})
target_compile_definitions (SDG_Engine PUBLIC ${Engine_CompileDefs})
