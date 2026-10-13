#ifndef RAYLIB_TEST_INPUT_MANAGER_H
#define RAYLIB_TEST_INPUT_MANAGER_H

#include "graphics.hpp"
#include "menu/side_menu.hpp"

class InputManager {
private:
    Graphics* graphics;
    SideMenu* menu;

public:
    InputManager(Graphics* graphics, SideMenu* sideMenu);

    void handle3DViewInput();

    void handleWSKeys();
};

#endif //RAYLIB_TEST_INPUT_MANAGER_H
