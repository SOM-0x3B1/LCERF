cmake_minimum_required(VERSION 4.2)
project(LCERF-Simulator)

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
        src/graphics.cpp
        src/input_manager.cpp
        src/devices/moving/robot.cpp
        src/robot_manager.cpp
        src/devices/device.cpp
        src/devices/device_static.cpp
        src/devices/device_movable.cpp
        src/device_manager.cpp
        src/devices/static/base_station.cpp
        src/cave.cpp
        src/network/wire.cpp
        src/chunk.cpp
        src/devices/attachable/interface_wireless.cpp
        src/devices/attachable/interface_wired.cpp
        src/devices/device_attachable.cpp
        src/devices/attachable/interface.cpp
        src/network/network_data.cpp
        src/simulator.cpp
        src/menu/menu.cpp
        src/menu/menu_window.cpp
        src/menu/side_menu.cpp
        src/menu/menu_content.cpp
        src/network/simulation_network_interface.cpp
        include/network/simulation_network_interface.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_custom_target(copy_simulator_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_dependencies(${PROJECT_NAME} copy_simulator_resources)