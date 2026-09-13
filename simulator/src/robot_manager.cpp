#include "../include/robot_manager.h++"

RobotManager::RobotManager(Graphics* graphics) {
    this->graphics = graphics;
    this->robots = std::vector<Robot*>();
}

void RobotManager::AddRobot(Robot* robot) {
    robots.push_back(robot);
}

void RobotManager::SetCameraToRobot(Robot* robot) {

}
