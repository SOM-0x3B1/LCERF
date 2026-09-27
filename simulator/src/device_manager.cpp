#include "../include/device_manager.hpp"

#include "../include/devices/attachable/interface.hpp"

std::vector<Interface*> DeviceManager::interfaces;

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

void DeviceManager::addInterface(Interface *interface) {
    interfaces.push_back(interface);
}

void DeviceManager::updateInterfaces() {
    for (auto interface: interfaces) {
        interface->updateConnections(interfaces);
    }
}