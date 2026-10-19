cmake_minimum_required(VERSION 4.2)
project(LCERF-Controller)

set(CMAKE_CXX_STANDARD 23)

set(RAYLIB_VERSION 6.0)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG ${RAYLIB_VERSION}
    )
    FetchContent_MakeAvailable(raylib)
endif ()

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/network_interface.cpp
        ../common/src/command.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)