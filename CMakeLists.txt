cmake_minimum_required(VERSION 3.26) # FetchContent is available in 3.11+
project(rayutils)
include(FetchContent)
include_directories(${CMAKE_SOURCE_DIR}/src)
set(CMAKE_CXX_STANDARD 17)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(json)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} src/main.cpp
        src/ray_utils.hpp
        src/entities/player.h
        src/entities/player.cpp
        src/ray_utils.cpp
        src/GameManager.h
        src/entities/finish.cpp
        src/entities/finish.h
        src/scenes/main_menu.hpp
        src/scenes/game.hpp
        src/scenes/levels/level_1.hpp
        src/scenes/game.cpp
        src/scenes/levels/level_1.cpp
        src/scenes/levels/level_2.cpp
        src/scenes/levels/level_2.hpp
        src/entities/recharge.cpp
        src/entities/recharge.h
        src/entities/enemy.cpp
        src/entities/enemy.h
        src/scenes/levels/level_3.cpp
        src/scenes/levels/level_3.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
