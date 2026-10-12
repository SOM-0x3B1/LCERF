#include "../include/input_manager.hpp"

#include "raylib.h"
#include "../include/menu/side_menu.hpp"

InputManager::InputManager(Graphics* graphics, SideMenu* sideMenu) {
    this->graphics = graphics;
    this->menu = sideMenu;
}

void InputManager::handle3DViewInput() {
    if (!menu->isEnabled()) {
        if (IsKeyDown(KEY_SPACE)) {
            graphics->moveCameraUp(0.05f);
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            graphics->moveCameraUp(-0.05f);
        }

        handleWSKeys();

        if (IsKeyDown(KEY_D))
            graphics->moveCameraRight(0.05f);
        if (IsKeyDown(KEY_A))
            graphics->moveCameraRight(-0.05f);

        if (IsKeyDown(KEY_RIGHT))
            graphics->rotateCameraYawAroundTarget(-0.05f);
        if (IsKeyDown(KEY_LEFT))
            graphics->rotateCameraYawAroundTarget(0.05f);
        if (IsKeyDown(KEY_UP))
            graphics->rotateCameraPitchAroundTarget(-0.05f);
        if (IsKeyDown(KEY_DOWN))
            graphics->rotateCameraPitchAroundTarget(0.05f);
    }
    else {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
            menu->stepUpSelectedOption();
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
            menu->stepDownSelectedOption();
    }

    if (IsKeyPressed(KEY_E))
        menu->toggle();
}

void InputManager::handleWSKeys() {
    bool isControlDown = IsKeyDown(KEY_LEFT_CONTROL);

    if (IsKeyDown(KEY_W)) {
        if (isControlDown)
            graphics->zoomCamera(0.05f);
        else
            graphics->moveCameraForward(0.05f);
    }
    if (IsKeyDown(KEY_S)) {
        if (isControlDown)
            graphics->zoomCamera(-0.05f);
        else
            graphics->moveCameraForward(-0.05f);
    }
}