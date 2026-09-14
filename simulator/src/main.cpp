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

#define ROBOT_COUNT 5

int main() {
    Graphics graphics;
    auto inputManager = InputManager(&graphics);
    auto deviceManager = DeviceManager(&graphics);
    auto cave = Cave();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    for (int i = 0; i < ROBOT_COUNT; i++) {
        Vector3 robotPosition = {.x = dist(mt), .y = 0, .z = dist(mt)};
        deviceManager.addRobot(new Robot(robotPosition));
    }

    deviceManager.addStaticDevice(new BaseStation(Vector3{0, 0, 0}));

    /*Model cave = LoadModel("valentine_tube_5cmXYZRGBI.asc");
    if (!IsModelValid(cave))
        throw std::exception{"invalid model"};*/

    Vector3 centerPosition = { .x = 0.0f, .y = 0.1f, .z = 0.0f };
    graphics.init(1000, 600, 30, {.x = 3, .y = 3, .z = 0}, centerPosition,
        "Cave Exploration Fleet Simulator");

    while (!WindowShouldClose())
    {
        graphics.updateCamera();
        inputManager.handle3DViewInput();

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(*graphics.getCamera());

        DrawGrid(20, 1);

        //DrawModelPoints(cave, centerPosition, 1.0f, WHITE);

        cave.drawPointCloud();
        deviceManager.drawAll();
        graphics.drawCursor();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    // UnloadModel(model);

    CloseWindow();
    return 0;
}