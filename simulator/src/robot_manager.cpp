#include "../include/robot_manager.hpp"

#include "raymath.h"

RobotManager::RobotManager(Graphics* graphics) {
    this->graphics = graphics;
    this->robots = std::vector<Robot*>();
}

RobotManager::~RobotManager() {
    for (auto robot: robots) {
        delete robot;
    }
    robots.clear();
}

void RobotManager::addRobot(Robot* robot) {
    robots.push_back(robot);
}

void RobotManager::drawRobots() {
    for (Robot* robot : robots) {
        robot->Draw();
    }
}

void RobotManager::setCameraToRobot(Robot* robot) {
    Camera* camera = graphics->getCamera();

    Vector3 newPos = Vector3Add(robot->getPosition(), graphics->getDeltaVectorFromTarget());

    camera->position = newPos;
    camera->target = robot->getPosition();
}
