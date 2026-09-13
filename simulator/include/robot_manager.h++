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

    void AddRobot(Robot* robot);

    void SetCameraToRobot(Robot* robot);
};



#endif //RAYLIB_TEST_ROBOT_MANAGER_H
