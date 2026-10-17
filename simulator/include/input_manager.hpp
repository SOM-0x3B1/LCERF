#ifndef RAYLIB_TEST_INPUT_MANAGER_H
#define RAYLIB_TEST_INPUT_MANAGER_H

#include "device_manager.hpp"
#include "graphics.hpp"
#include "../include/menu/menu.hpp"

class InputManager {
private:
    Graphics* graphics;
    DeviceManager* deviceManager;
    Menu* menu;

public:
    InputManager(Graphics* graphics, DeviceManager* deviceManager, Menu* menu);

    void handle3DViewInput();

    void handleWSKeys();
};

#endif //RAYLIB_TEST_INPUT_MANAGER_H
