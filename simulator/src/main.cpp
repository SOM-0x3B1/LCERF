#include "raylib.h"
#include <random>

#include "../include/cave.hpp"
#include "../include/device_manager.hpp"
#include "../include/graphics.hpp"
#include "../include/input_manager.hpp"
#include "../include/simulator.hpp"
#include "../include/menu/menu.hpp"

int main() {
    Graphics graphics;
    Vector3 centerPosition = { .x = 0.0f, .y = 0.1f, .z = 0.0f };
    graphics.init(1024, 720, 60, {.x = 1.5, .y = 1.5, .z = 0}, centerPosition,
        "Lunar Cave Exploration - Simulator", 12);

    auto menu = Menu(&graphics);
    auto deviceManager = DeviceManager(&graphics, &menu);
    auto inputManager = InputManager(&graphics, &deviceManager, &menu);
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

        DrawGrid(20, 1);
        cave.drawPointCloud();
        deviceManager.focusCameraOnSelectedDevice();
        deviceManager.drawAll3D();
        graphics.drawCursor();

        EndMode3D();

        menu.draw();
        DrawFPS(10, 10);
        deviceManager.drawAll2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
