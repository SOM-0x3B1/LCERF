#ifndef RAYLIB_TEST_ROBOT_MANAGER_H
#define RAYLIB_TEST_ROBOT_MANAGER_H

#include <vector>

#include "graphics.h++"
#include "robot.h++"

class RobotManager {
private:
    int currentRobotIndex = 0;
    std::vector<Robot*> robots;
    Graphics* graphics;

public:
    explicit RobotManager(Graphics* graphics);
    ~RobotManager();

    void addRobot(Robot* robot);

    void drawRobots();

    void setCameraToRobot(Robot* robot);
};

#endif //RAYLIB_TEST_ROBOT_MANAGER_H
