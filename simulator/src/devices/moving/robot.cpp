#include "../../../include/devices/moving/robot.hpp"

#include <random>

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

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    Vector3 robotPosition = position;
    for (int i = 0; i < 20; i++) {
        robotPosition = Vector3Add(robotPosition, {.x = dist(mt), .y = 0, .z = dist(mt)});
        movementCheckpoints.push(robotPosition);
    }
}

void Robot::move() {
    Vector3 currCheckPoint = movementCheckpoints.front();

    float distance = Vector3Distance(position, currCheckPoint);
    if (distance < 0.1) {
        movementCheckpoints.pop();
        currCheckPoint = movementCheckpoints.front();
    }

    Vector3 fullMove = Vector3MoveTowards(position, currCheckPoint, 0.01);
    Vector3 dV = Vector3Subtract(fullMove, position);
    DeviceMovable::move(dV);
}

void Robot::connectNewWireTo(InterfaceWired *interface) {
    wiredInterface->connectNewWireToOtherInterface(interface);
}

void Robot::draw() {
    DrawCube(position, 0.15, 0.1, 0.2, YELLOW);
    drawAttachedDevices();
}

void Robot::simulationStep() {
    move();
}
