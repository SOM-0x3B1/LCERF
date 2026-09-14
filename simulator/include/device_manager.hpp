#ifndef LCERF_DEVICE_MANAGER_H
#define LCERF_DEVICE_MANAGER_H

#include <vector>
#include "device.hpp"
#include "robot_manager.hpp"

class DeviceManager {
private:
    Graphics* graphics;

    std::vector<Device*> devices;
    RobotManager robotManager;

public:
    explicit DeviceManager(Graphics* graphics);

    void DrawAll();

    void AddRobot(Robot* robot);
};


#endif //LCERF_DEVICE_MANAGER_H
