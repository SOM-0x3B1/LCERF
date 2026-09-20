#include "raylib.h"
#include "raymath.h"
#include <random>

#include "../include/cave.hpp"
#include "../include/device_manager.hpp"
#include "../include/graphics.hpp"
#include "../include/input_manager.hpp"
#include "../include/devices/movable/robot.hpp"
#include "../include/robot_manager.hpp"
#include "../include/devices/static/base_station.hpp"
#include "../include/devices/static/wire.hpp"

#define ROBOT_COUNT 5

int main() {
    Graphics graphics;
    Vector3 centerPosition = { .x = 0.0f, .y = 0.1f, .z = 0.0f };
    graphics.init(1000, 600, 60, {.x = 1, .y = 1, .z = 0}, centerPosition,
        "Lunar Cave Exploration - Simulator");

    auto inputManager = InputManager(&graphics);
    auto deviceManager = DeviceManager(&graphics);
    auto cave = Cave("model.obj", &graphics, {0.0f, 0.1f, 0.0f});

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    deviceManager.addStaticDevice(new BaseStation(Vector3{0, 0, 0}, &graphics));
    for (int i = 0; i < ROBOT_COUNT; i++) {
        Vector3 robotPosition = {.x = dist(mt), .y = 0, .z = dist(mt)};
        deviceManager.addRobot(new Robot(robotPosition, &graphics));
        deviceManager.addStaticDevice(new Wire(robotPosition, Vector3{0, 0, 0}, &graphics));
    }

    while (!WindowShouldClose())
    {
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