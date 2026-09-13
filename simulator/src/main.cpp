#include "raylib.h"
#include "raymath.h"
#include <random>

#include "../include/graphics.h++"
#include "../include/input_manager.h++"
#include "../include/robot.h++"
#include "../include/robot_manager.h++"

#define CAVE_POINT_COUNT 2000
#define ROBOT_COUNT 10

int main() {
    Graphics graphics;
    auto inputManager = InputManager(&graphics);
    auto robotManager = RobotManager(&graphics);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    Vector3 cavePoints[CAVE_POINT_COUNT];
    for (int i = 0; i < CAVE_POINT_COUNT; i++)
        cavePoints[i] = { dist(mt), dist(mt) / 2.0f + 1.0f, dist(mt) };

    for (int i = 0; i < ROBOT_COUNT; i++) {
        Vector3 robotPosition = {dist(mt), dist(mt) / 2.0f + 1.0f, dist(mt)};
        robotManager.addRobot(new Robot(robotPosition));
    }

    /*Model cave = LoadModel("valentine_tube_5cmXYZRGBI.asc");
    if (!IsModelValid(cave))
        throw std::exception{"invalid model"};*/

    Vector3 centerPosition = { 0.0f, 0.0f, 0.0f };
    graphics.init(1000, 600, 30, {3, 3, 0}, centerPosition,
        "Cave Exploration Fleet Simulator");

    while (!WindowShouldClose())
    {
        graphics.updateCamera();
        inputManager.handle3DViewInput();

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(*graphics.getCamera());

        DrawGrid(10, 1);

        for (int i = 0; i < CAVE_POINT_COUNT; i++) {
            DrawCube(cavePoints[i],  0.01, 0.01, 0.01,
                Graphics::getProximityColor(graphics.getCamera()->target, cavePoints[i]));
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