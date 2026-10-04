#include "../include/device_manager.hpp"

#include "../include/devices/attachable/interface.hpp"

std::vector<Device*> DeviceManager::devices;
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
    robot->connectNewWireTo(baseStation->getWiredInterface());
}

void DeviceManager::addStaticDevice(DeviceStatic *device) {
    devices.push_back(device);
}

void DeviceManager::setBaseStation(BaseStation* station) {
    this->baseStation = station;
}

void DeviceManager::addInterface(Interface *interface) {
    interfaces.push_back(interface);
}

void DeviceManager::updateInterfaces() {
    for (auto interface: interfaces) {
        interface->updateConnections();
    }
}

std::vector<Device*>* DeviceManager::getDeviceCollection() {
    return &devices;
}

std::vector<Interface*>* DeviceManager::getInterfaceCollection() {
    return &interfaces;
}
