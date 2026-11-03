#include "../include/robot_manager.hpp"
#include "../../common/include/command.hpp"

#include "raymath.h"

RobotManager::RobotManager(Graphics* graphics, Menu* menu, SimulationNetworkInterface* controllerInterface) {
    this->graphics = graphics;
    this->controllerInterface = controllerInterface;
    this->robots = std::vector<Robot*>();
    this->menu = menu;
    SideMenuWithSubMenus* sideMenus;

    registerMenus();
}

RobotManager::~RobotManager() {
    for (auto robot: robots) {
        delete robot;
    }
    robots.clear();
}

void RobotManager::registerMenus() {
    menu->addSectionToMainSideMenu(
        new MenuContent(
            MenuContentType::OPTION,
            "Robot manager",
            new OptionActionNavigation({"robot_manager"}))
    );

    auto sideMenu = new SideMenu(graphics);
    sideMenu->addToLayout(std::vector{
        new MenuContent(MenuContentType::TITLE, "Robot manager"),
        new MenuContent(MenuContentType::LABEL, "Robots"),
    });
    this->sideMenus = new SideMenuWithSubMenus(sideMenu);
    menu->addSubSideMenu({}, "robot_manager", this->sideMenus);
}

SideMenuWithSubMenus* RobotManager::getSideMenus() {
    return sideMenus;
}

void RobotManager::addRobot(Robot* robot) {
    // TODO: ?
    robot->assignID(robots.size());
    robot->addControllerInterface(controllerInterface);
    robots.push_back(robot);
}

Robot* RobotManager::getRobotByID(int id) {
    return robots[id];
}

void RobotManager::registerRobots() {
    for (auto robot: robots) {
        controllerInterface->sendData(CommandRobotRegister(robot->getID()).toString());
    }
    controllerInterface->sendData(CommandRobotRegisterFinish().toString());
}

void RobotManager::drawRobots() {
    for (Robot* robot : robots) {
        robot->draw3D();
    }
}

void RobotManager::setCameraToRobot(Robot* robot, Graphics* graphics) {
    Camera* camera = graphics->getCamera();

    Vector3 newPos = Vector3Add(robot->getPosition(), graphics->getDeltaVectorFromTarget());

    camera->position = newPos;
    camera->target = robot->getPosition();
}
