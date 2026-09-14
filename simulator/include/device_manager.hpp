#ifndef LCERF_DEVICE_MANAGER_H
#define LCERF_DEVICE_MANAGER_H

#include <vector>
#include "devices/device.hpp"
#include "robot_manager.hpp"
#include "devices/device_static.hpp"

class DeviceManager {
private:
    Graphics* graphics;

    std::vector<Device*> devices;
    RobotManager robotManager;

public:
    explicit DeviceManager(Graphics* graphics);

    void drawAll();

    void addRobot(Robot* robot);

    void addStaticDevice(DeviceStatic* device);
};


#endif //LCERF_DEVICE_MANAGER_H
