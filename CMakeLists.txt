cmake_minimum_required(VERSION 4.2)
project(LCERF)

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

add_executable(${PROJECT_NAME} simulator/src/main.cpp
        simulator/src/graphics.cpp
        simulator/src/input_manager.cpp
        simulator/src/devices/movable/robot.cpp
        simulator/src/robot_manager.cpp
        simulator/src/devices/device.cpp
        simulator/src/devices/device_static.cpp
        simulator/src/devices/device_movable.cpp
        simulator/src/device_manager.cpp
        simulator/src/devices/static/base_station.cpp
        simulator/src/cave.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)