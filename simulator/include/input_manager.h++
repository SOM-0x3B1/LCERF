#ifndef RAYLIB_TEST_INPUT_MANAGER_H
#define RAYLIB_TEST_INPUT_MANAGER_H

#include "robot.h++"
#include "../include/graphics.h++"

class InputManager
{
public:
    static void handle3DViewInput(Graphics& graphics);
    static void jumpToRobot(Graphics& graphics, Robot robot);
};

#endif //RAYLIB_TEST_INPUT_MANAGER_H
