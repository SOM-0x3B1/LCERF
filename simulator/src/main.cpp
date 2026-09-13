#include "raylib.h"
#include "raymath.h"
#include <random>

#include "../include/graphics.h++"
#include "../include/input_manager.h++"
#include "../include/robot.h++"

#define CAVE_POINT_COUNT 2000
#define ROBOT_COUNT 10

int main() {
    Graphics graphics;
    Vector3 centerPosition = { 0.0f, 0.0f, 0.0f };

    graphics.init(1000, 600, 30, {3, 3, 0}, centerPosition,
        "Cave Exploration Fleet Simulator");


    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    Vector3 cavePoints[CAVE_POINT_COUNT];
    for (int i = 0; i < CAVE_POINT_COUNT; i++)
        cavePoints[i] = { dist(mt), dist(mt) / 2.0f + 1.0f, dist(mt) };

    Robot robots[ROBOT_COUNT];
    for (int i = 0; i < ROBOT_COUNT; i++)
        robots[i] = Robot(dist(mt), dist(mt) / 2.0f + 1.0f, dist(mt));


    /*Model cave = LoadModel("valentine_tube_5cmXYZRGBI.asc");
    if (!IsModelValid(cave))
        throw std::exception{"invalid model"};*/

    // Main game loop
    while (!WindowShouldClose())
    {
        graphics.updateCamera();

        InputManager::handle3DViewInput(graphics);


        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(*graphics.getCamera());

        DrawGrid(10, 1);
        DrawSphere(graphics.getCamera()->target, 0.05f, WHITE);
        //DrawSphereWires(centerPosition, 1.0f, 10, 10, YELLOW);
        for (int i = 0; i < CAVE_POINT_COUNT; i++) {
            DrawCube(cavePoints[i],  0.01, 0.01, 0.01,
                Graphics::getProximityColor(graphics.getCamera()->target, cavePoints[i]));
        }
        //DrawModelPoints(cave, centerPosition, 1.0f, WHITE);

        for (int i = 0; i < ROBOT_COUNT; i++) {
            Vector3 robotPosition = robots[i].getPosition();
            DrawCube(robotPosition,  0.2, 0.1, 0.15,
                Graphics::getProximityColor(graphics.getCamera()->target, robotPosition));
        }

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    // UnloadModel(model);

    CloseWindow();
    return 0;
}