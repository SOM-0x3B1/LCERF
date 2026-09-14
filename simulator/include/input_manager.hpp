#ifndef RAYLIB_TEST_INPUT_MANAGER_H
#define RAYLIB_TEST_INPUT_MANAGER_H

#include "robot.hpp"
#include "../include/graphics.hpp"

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
