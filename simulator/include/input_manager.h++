#ifndef RAYLIB_TEST_INPUT_MANAGER_H
#define RAYLIB_TEST_INPUT_MANAGER_H

#include "robot.h++"
#include "../include/graphics.h++"

class InputManager
{
private:
    Graphics*graphics;

public:
    InputManager(Graphics* graphics);

    void handle3DViewInput();

    void handleWSKeys();
};

#endif //RAYLIB_TEST_INPUT_MANAGER_H
