cmake_minimum_required(VERSION 3.16)
set(PROJ ENGINE)
set(CMAKE_CXX_STANDARD 17)
project(${PROJ})

if (APPLE)
    # Universal binary
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    set(PLATFORM_LIBS "-framework OpenGL")
elseif(WIN32)
    set(PLATFORM_LIBS opengl32)
endif()

include_directories(
        lib/SDL/include
        lib/sdl-gpu/include)

set(ENGINE_SRCS
        ${ENGINE_SRCS}
        src/main.cpp
        src/Shader.cpp
        src/Shader.h src/Game.cpp src/Game.h src/Platform.h src/Logging.cpp src/FileSys.cpp src/FileSys.h src/XMLReader.cpp src/XMLReader.h src/Scene.cpp src/Scene.h src/Input.cpp src/Input.h src/ContentMgr.cpp src/ContentMgr.h src/Texture2D.h src/Texture2D.cpp)

add_executable(ENGINE ${ENGINE_SRCS})

add_subdirectory(lib/SDL)
set(SDL2_INCLUDE_DIR SDL/include)
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)
add_subdirectory(lib/sdl-gpu)
add_subdirectory(lib/tinyxml2)
add_subdirectory(lib/spdlog)

target_include_directories(ENGINE PRIVATE
        lib/spdlog/include)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(ENGINE PRIVATE DEBUG=1)
    set(CONFIG_LIBS spdlog)
else()
    set(CONFIG_LIBS)
endif()

target_link_libraries(ENGINE PUBLIC
        SDL2
        SDL_gpu
        tinyxml2
        ${CONFIG_LIBS}
        ${PLATFORM_LIBS}
        )

add_custom_target(AssetSymlink
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)






