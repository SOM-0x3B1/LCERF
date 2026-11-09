#ifndef LCERF_CONTROLLER_ROBOT_MANAGER_HPP
#define LCERF_CONTROLLER_ROBOT_MANAGER_HPP

#include <vector>
#include "network_interface.hpp"
#include "robot.hpp"

class RobotManager {
private:
    bool ready;
    NetworkInterface* networkInterface;
    std::vector<Robot> robots;

public:
    explicit RobotManager(NetworkInterface* networkInterface);

    bool isReady();

    void registerRobot(int id);
    void finishRegistration();
    void completeWaypoint(int robotID);

    void updateRobots();
    void clearWaypoints(int id);
};


#endif //LCERF_CONTROLLER_ROBOT_MANAGER_HPP
