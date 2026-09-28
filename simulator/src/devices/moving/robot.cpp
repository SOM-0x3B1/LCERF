#include "../../../include/devices/moving/robot.hpp"

#include "raymath.h"
#include "../../../include/device_manager.hpp"
#include "../../../include/devices/attachable/interface_wireless.hpp"

Robot::Robot(Vector3 position, Graphics* graphics) : DeviceMovable(position, graphics) {
    Vector3 wirelessNetworkInterfacePos = Vector3Add(position, Vector3(0, 0.05, 0.045));
    auto wirelessNetworkInterface = new InterfaceWireless(wirelessNetworkInterfacePos, graphics, this->id, 1.5f, this);
    attachedDevices.push_back(wirelessNetworkInterface);
    DeviceManager::addInterface(wirelessNetworkInterface);
    this->wirelessInterface = wirelessNetworkInterface;

    Vector3 wiredNetworkInterfacePos = Vector3Add(position, Vector3(0, 0.05, -0.045));
    auto wiredNetworkInterface = new InterfaceWired(wiredNetworkInterfacePos, graphics, this->id, this);
    attachedDevices.push_back(wiredNetworkInterface);
    DeviceManager::addInterface(wiredNetworkInterface);
    this->wiredInterface = wiredNetworkInterface;
}

void Robot::connectNewWireTo(InterfaceWired *interface) {
    wiredInterface->connectNewWireToOtherInterface(interface);
}

void Robot::draw() {
    DrawCube(position, 0.15, 0.1, 0.2, YELLOW);
    drawAttachedDevices();
}
