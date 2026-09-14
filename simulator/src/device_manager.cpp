#include "../include/device_manager.hpp"

DeviceManager::DeviceManager(Graphics *graphics) : robotManager(graphics) {
    this->graphics = graphics;
}

void DeviceManager::DrawAll() {
    for (auto device: devices) {
        device->Draw();
    }
}

void DeviceManager::AddRobot(Robot* robot) {
    devices.push_back(robot);
    robotManager.addRobot(robot);
}
