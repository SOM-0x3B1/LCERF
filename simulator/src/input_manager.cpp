#include "../include/input_manager.h++"

#include "raylib.h"

void InputManager::handle3DViewInput(Graphics& graphics) {
    if (IsKeyDown(KEY_SPACE))
        graphics.moveCameraUp(0.05f);
    if (IsKeyDown(KEY_LEFT_SHIFT))
        graphics.moveCameraUp(-0.05f);

    if (IsKeyDown(KEY_W))
        graphics.moveCameraForward(0.05f);
    if (IsKeyDown(KEY_S))
        graphics.moveCameraForward(-0.05f);
    if (IsKeyDown(KEY_D))
        graphics.moveCameraRight(0.05f);
    if (IsKeyDown(KEY_A))
        graphics.moveCameraRight(-0.05f);

    if (IsKeyDown(KEY_RIGHT))
        graphics.rotateCameraYawAroundTarget(-0.05f);
    if (IsKeyDown(KEY_LEFT))
        graphics.rotateCameraYawAroundTarget(0.05f);
    if (IsKeyDown(KEY_UP)) {
        graphics.rotateCameraPitchAroundTarget(-0.05f);
    }
    if (IsKeyDown(KEY_DOWN)) {
        graphics.rotateCameraPitchAroundTarget(0.05f);
    }
}

void InputManager::jumpToRobot(Graphics& graphics, Robot robot) {
    graphics.getCamera()->position = robot.getPosition();
}
