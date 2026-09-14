#include "../include/device_manager.hpp"

DeviceManager::DeviceManager(Graphics *graphics) : robotManager(graphics) {
    this->graphics = graphics;
}

void DeviceManager::drawAll() {
    for (auto device: devices) {
        device->draw();
    }
}

void DeviceManager::addRobot(Robot* robot) {
    devices.push_back(robot);
    robotManager.addRobot(robot);
}

void DeviceManager::addStaticDevice(DeviceStatic *device) {
    devices.push_back(device);
}
