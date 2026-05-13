cmake_minimum_required(VERSION 3.20)

project(NankaiRhythm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Avoid building raylib examples/games.
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

FetchContent_MakeAvailable(raylib)

add_executable(NankaiRhythm
    src/main.cpp
    src/Game.cpp
    src/MenuScene.cpp
    src/HelpScene.cpp
    src/PlayScene.cpp
    src/ResultScene.cpp
    src/Note.cpp
    src/Chart.cpp
    src/ScoreManager.cpp
)

target_include_directories(NankaiRhythm PRIVATE src)
target_link_libraries(NankaiRhythm PRIVATE raylib)

# Copy assets next to the executable so relative paths work in VSCode/CMake Tools.
add_custom_command(TARGET NankaiRhythm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:NankaiRhythm>/assets
)
