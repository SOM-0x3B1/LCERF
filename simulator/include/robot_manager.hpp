#ifndef RAYLIB_TEST_ROBOT_MANAGER_H
#define RAYLIB_TEST_ROBOT_MANAGER_H

#include <vector>

#include "graphics.hpp"
#include "devices/moving/robot.hpp"
#include "menu/menu.hpp"
#include "network/external_network_interface.hpp"

class RobotManager {
private:
    std::vector<Robot*> robots;
    Graphics* graphics;
    Menu* menu;
    SideMenuWithSubMenus* sideMenus{};
    ExternalNetworkInterface* controllerInterface;

public:
    explicit RobotManager(Graphics* graphics, Menu* menu, ExternalNetworkInterface* controllerInterface);
    ~RobotManager();

    void registerMenus();
    SideMenuWithSubMenus* getSideMenus();

    void addRobot(Robot* robot);
    Robot* getRobotByID(int id);
    void registerRobots();

    void drawRobots();

    static void setCameraToRobot(Robot* robot, Graphics* graphics);
};

#endif //RAYLIB_TEST_ROBOT_MANAGER_H
