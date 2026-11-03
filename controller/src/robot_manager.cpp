#include "../include/robot_manager.hpp"
#include <random>
#include <thread>

#include "raymath.h"
#include "../../common/include/command.hpp"

RobotManager::RobotManager(NetworkInterface* networkInterface) {
    this->ready = false;
    this->networkInterface = networkInterface;
}

bool RobotManager::isReady() {
    return ready;
}

void RobotManager::registerRobot(int id) {
    robots.push_back(Robot(id));
}

void RobotManager::finishRegistration() {
    ready = true;
}

void RobotManager::completeWaypoint(int robotID) {
    robots[robotID].completeWaypoint();
}

void RobotManager::updateRobots() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    for (int i = 0; i < robots.size(); ++i) {
        auto waypoints = robots[i].getWaypoints();
        if (waypoints->size() < 2) {
            auto lastWp = waypoints->empty() ? Vector2(0, 0) : waypoints->back();
            auto deltaWp = Vector2(dist(mt) - 0.5f, dist(mt));
            Vector2 newWp = Vector2Add(lastWp, deltaWp);
            robots[i].addWaypoint(newWp);
            networkInterface->sendData(CommandRobotMoveToPosition(robots[i].getID(), newWp.x, newWp.y).toString());
        }
    }
}
