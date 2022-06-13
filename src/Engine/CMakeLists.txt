# [ SDG_Engine ] ====================================================
# ----- Sources -----------------------------------------------------
set(Engine_PrecompiledHeaders Lib/Private/Pch.h)
set(TinyXML2_Sources
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.h
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.cpp)
set(Nfont_Sources
    ${CMAKE_SOURCE_DIR}/lib/nfont/NFont/NFont.cpp
    ${CMAKE_SOURCE_DIR}/lib/nfont/NFont/NFont.h
    ${CMAKE_SOURCE_DIR}/lib/nfont/SDL_FontCache/SDL_FontCache.c
    ${CMAKE_SOURCE_DIR}/lib/nfont/SDL_FontCache/SDL_FontCache.h)
#set(Engine_Sources
add_library(SDG_Engine STATIC
        ${TinyXML2_Sources}
        ${Nfont_Sources}

        "Engine.cpp" "Engine.h"
        Game/AssetMgr.cpp Game/AssetMgr.h

        Lib/ClassMacros.h

        # Debug
        Debug/Assert.h
        Debug/Assert.cpp
        Debug/Log.h
        Debug/Log.cpp
        Debug/LogImpl.h
        Debug/Trace.h 

        EntryPoint.cpp

        # Exceptions
        Exceptions/AssertionException.h Exceptions/AssertionException.cpp
         
        Exceptions/NullReferenceException.h 
        Exceptions/InvalidArgumentException.cpp Exceptions/InvalidArgumentException.h   
        Exceptions/DivisionByZeroException.h
        Exceptions/Exception.h Exceptions/Exception.cpp 
         
        Exceptions/OutOfRangeException.h Exceptions/OutOfRangeException.cpp 
        Exceptions/RuntimeException.h

        # FileSys
        "Game/Datatypes/AppConfig.h"
        FileSys/FileSys.cpp FileSys/FileSys.h
        FileSys/Private/IO.cpp FileSys/Private/IO.h
        FileSys/File.cpp Filesys/File.h
        FileSys/Path.cpp FileSys/Path.h
        "FileSys/Xml/XmlLoadable.cpp" "FileSys/Xml/XmlLoadable.h"

        Game/Entity.cpp Game/Entity.h
        Game/ComponentList.cpp Game/ComponentList.h Game/Component.h
        Game/Scene.cpp Game/Scene.h
        Game/ServiceProvider.h

        Graphics/Camera2D.cpp Graphics/Camera2D.h
        Graphics/WindowMgr.cpp Graphics/WindowMgr.h
        Graphics/Window.cpp Graphics/Window.h
        Graphics/Private/RendererType.h
        Graphics/Shader.cpp Graphics/Shader.h
        Graphics/Color.h Graphics/Color.cpp
        Graphics/SpriteBatch.cpp Graphics/SpriteBatch.h
        Graphics/Texture.h Graphics/Texture.cpp
         
        Graphics/RenderTarget.cpp Graphics/RenderTarget.h
        Graphics/Flip.h Graphics/Flip.cpp 
        Graphics/Private/TranslateFlip.h Graphics/Private/TranslateFlip.cpp
        Graphics/Private/Conversions.h
        Graphics/Sprite.h Graphics/Sprite.cpp 
        Graphics/Frame.h Graphics/Frame.cpp
        Graphics/SpriteRenderer.h Graphics/SpriteRenderer.cpp

        Input/Input.cpp Input/Input.h
        Input/Key.h
        Input/Keyboard.h Input/Keyboard.cpp
        Input/InputComponent.h
        Input/Mouse.cpp Input/Mouse.h Input/MButton.h
        Input/Gamepad.h Input/Gamepad.cpp 
        Input/Button.h Input/Button.cpp 
        Input/GamepadType.h

        Math/Rand.cpp Math/Rand.h
        Math/Math.h Math/Math.cpp
        Math/Vector2.h
        Math/Vector3.h
        Math/Tween.cpp Math/Tween.h Math/TweenFunctions.cpp Math/TweenFunctions.h
        Math/Matrix4x4.cpp Math/Matrix4x4.h
        Math/Rectangle.h
        Math/MathConstants.h 
        Math/MathShape.h Math/MathShape.cpp
        Math/Private/Conversions.h
        Math/Tweener.cpp Math/Tweener.h
        Math/Intersection.h Math/Circle.h

        "Platform.h"

        "Dynamic/Array.h"
        Lib/Buffer.cpp Lib/Buffer.h
        Lib/Delegate.h
        Lib/Endian.h Lib/Endian.cpp
        Lib/FixedPool.h 
        Lib/Memory.h
        Lib/Pool.h
        Lib/PoolID.h 
        Lib/Private/PoolNullIndex.h 
        Lib/Private/PoolNullIndex.cpp
        Lib/Ref.h
        Lib/Shared.h 
        Lib/String.h Lib/String.cpp
        Lib/StringView.h Lib/StringView.cpp
        Lib/Swap.h
        Lib/Unique.h

        Logic/DynamicState.h Logic/DynamicStateMachine.h Logic/DynamicState.cpp Logic/DynamicStateMachine.cpp

        "Lib/Position.h"

        Time/AppTime.cpp Time/AppTime.h
        Time/Chronogram.h Time/Chronogram.cpp 
        Time/TimeUnit.h Time/TimeUnit.cpp 
        Time/Timer.h Time/Timer.cpp 
        Time/Duration.h Time/Duration.cpp
        
  "Graphics/Font.h" "Graphics/Font.cpp" "Lib/Enum.h" "Lib/Private/Fmt.h" "Exceptions/UncaughtCaseException.h" "Lib/Ref.inl" "Lib/Array.inl" "Lib/Delegate.inl" "FileSys/Xml/XmlElement.h" "FileSys/Xml/XmlElement.cpp" "FileSys/Xml/XmlAttribute.h" "FileSys/Xml/XmlAttribute.cpp" "FileSys/Xml/XmlDocument.h" "FileSys/Xml/XmlDocument.cpp" "FileSys/Xml/Private/XmlDocument_Impl.h"  "Exceptions/XmlValidationException.h" "FileSys/Xml/XmlValidation.h" "Exceptions/XmlValidationException.cpp" "Game/Datatypes/AppConfig.cpp" "Exceptions/XmlFormattingException.h" "Graphics/Private/NFont.h" 
 "Lib/Version.h" "Lib/Version.cpp" "Lib/Platform.cpp" "Debug/Private/spdlog.h" "Lib/RAIterator.h" "Lib/ConstRAIterator.h" "Exceptions/Fwd.h" "Exceptions/Fwd.cpp" "Lib/Algorithm.h" "Lib/TypeTraits.h" "Lib/Concepts.h" "Lib/Int.h" 
 "Dynamic/Object.h" "Dynamic/Struct.h" "Dynamic/Struct.cpp" "Dynamic/Object.cpp" "Dynamic/Array.h"  "Dynamic/Array.cpp"   "Filesys/Json.h" "Filesys/Json.cpp" "Exceptions/XmlException.h"   "Exceptions/LogicException.h" "Exceptions/DomainException.h" "Exceptions/FileLoadingException.h")

# -----  Includes  ----------------------------------------------------
set(Engine_Includes
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/spdlog/include
        ${CMAKE_SOURCE_DIR}/lib/SDL/include
        ${CMAKE_SOURCE_DIR}/lib/sdl-gpu/include
        ${CMAKE_SOURCE_DIR}/lib/tinyxml2
        ${CMAKE_SOURCE_DIR}/lib/glm
        ${CMAKE_SOURCE_DIR}/lib/nfont/NFont
        ${CMAKE_SOURCE_DIR}/lib/nfont/SDL_FontCache
        ${CMAKE_SOURCE_DIR}/lib/json/include
        ${CMAKE_SOURCE_DIR}/lib/SDL_ttf
)

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
        set(CONFIG_Libraries SDL2 SDL2main spdlog)
    else()
        set(CONFIG_Libraries SDL2 spdlog)
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
    set(CMAKE_CXX_FLAGS "-O0 -sUSE_SDL=2 -sUSE_SDL_TTF=2 -fexceptions")
    set(CMAKE_EXE_LINKER_FLAGS "-O0 -sASSERTIONS -sASYNCIFY -sUSE_WEBGL2=1 -sWASM=2 -sMAX_WEBGL_VERSION=2 -LLD_REPORT_UNDEFINED -sNO_DISABLE_EXCEPTION_CATCHING")
endif()

set (Engine_Libraries
        ${CONFIG_Libraries}
        ${PLATFORM_Libraries}
        SDL_gpu
        SDL2_ttf)

# ----- Commit the Settings ----------------------------------------
#add_library                (SDG_Engine STATIC ${Engine_Sources})
target_include_directories (SDG_Engine PUBLIC ${Engine_Includes})
if (NOT EMSCRIPTEN)
    target_precompile_headers  (SDG_Engine PRIVATE 
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/src/Engine/Lib/Private/Pch.h>")
endif()
target_link_libraries      (SDG_Engine PUBLIC ${Engine_Libraries})
target_compile_definitions (SDG_Engine PUBLIC ${Engine_CompileDefs} "FC_USE_SDL_GPU")
