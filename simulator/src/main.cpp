#include "raylib.h"
#include "raymath.h"
#include <random>

#include "../include/graphics.h++"
#include "../include/input_manager.h++"
#include "../include/robot.h++"
#include "../include/robot_manager.h++"

#define CAVE_POINT_COUNT 2000
#define ROBOT_COUNT 5

int main() {
    Graphics graphics;
    auto inputManager = InputManager(&graphics);
    auto robotManager = RobotManager(&graphics);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    Vector3 cavePoints[CAVE_POINT_COUNT];
    for (auto & cavePoint : cavePoints)
        cavePoint = { .x = dist(mt), .y = dist(mt) / 2.0f + 1.0f, .z = dist(mt) };

    for (int i = 0; i < ROBOT_COUNT; i++) {
        Vector3 robotPosition = {.x = dist(mt), .y = 0, .z = dist(mt)};
        robotManager.addRobot(new Robot(robotPosition));
    }

    /*Model cave = LoadModel("valentine_tube_5cmXYZRGBI.asc");
    if (!IsModelValid(cave))
        throw std::exception{"invalid model"};*/

    Vector3 centerPosition = { .x = 0.0f, .y = 0.0f, .z = 0.0f };
    graphics.init(1000, 600, 30, {.x = 3, .y = 3, .z = 0}, centerPosition,
        "Cave Exploration Fleet Simulator");

    while (!WindowShouldClose())
    {
        graphics.updateCamera();
        inputManager.handle3DViewInput();

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(*graphics.getCamera());

        DrawGrid(10, 1);

        for (auto cavePoint : cavePoints) {
            DrawCube(cavePoint,  0.01, 0.01, 0.01,
                Graphics::getProximityColor(graphics.getTarget(), cavePoint));
        }
        //DrawModelPoints(cave, centerPosition, 1.0f, WHITE);

        robotManager.drawRobots();
        graphics.drawCursor();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    // UnloadModel(model);

    CloseWindow();
    return 0;
}