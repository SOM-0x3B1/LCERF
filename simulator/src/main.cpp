#include "raylib.h"
#include "raymath.h"
#include <random>

#include "../include/cave.hpp"
#include "../include/device_manager.hpp"
#include "../include/graphics.hpp"
#include "../include/input_manager.hpp"
#include "../include/devices/moving/robot.hpp"
#include "../include/robot_manager.hpp"
#include "../include/simulator.hpp"
#include "../include/devices/static/base_station.hpp"
#include "../include/network/wire.hpp"

int main() {
    Graphics graphics;
    Vector3 centerPosition = { .x = 0.0f, .y = 0.1f, .z = 0.0f };
    graphics.init(1024, 720, 60, {.x = 1.5, .y = 1.5, .z = 0}, centerPosition,
        "Lunar Cave Exploration - Simulator", 12);

    auto inputManager = InputManager(&graphics);
    auto deviceManager = DeviceManager(&graphics);
    auto cave = Cave("pisgah-realigned-reduced.obj", &graphics, {0.0f, 0.1f, 0.0f});

    auto simulator = Simulator(&cave, &deviceManager, &graphics);
    simulator.init();

    while (!WindowShouldClose())
    {
        DeviceManager::updateInterfaces();
        simulator.step();

        graphics.updateCamera();
        inputManager.handle3DViewInput();

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(*graphics.getCamera());

        //DrawModelPoints(cave, centerPosition, 1.0f, WHITE);
        DrawGrid(20, 1);
        cave.drawPointCloud();
        deviceManager.drawAll();
        graphics.drawCursor();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}