#include "../../../include/devices/moving/robot.hpp"

#include <random>

#include "raymath.h"
#include "../../../include/device_manager.hpp"
#include "../../../include/devices/attachable/interface_wireless.hpp"

Robot::Robot(Vector3 position, Graphics* graphics) : DeviceMovable(position, graphics) {
    width = 0.15f;
    height = 0.1f;
    length = 0.2f;

    float halfWidth =  width / 2;
    float halfLen =  length / 2;
    float bottomY = position.y - height / 2;
    supportPoints.push_back(Vector3(position.x + halfWidth, bottomY, position.z + halfLen));
    supportPoints.push_back(Vector3(position.x - halfWidth, bottomY, position.z + halfLen));
    supportPoints.push_back(Vector3(position.x + halfWidth, bottomY, position.z - halfLen));
    supportPoints.push_back(Vector3(position.x - halfWidth, bottomY, position.z - halfLen));

    Vector3 wirelessNetworkInterfacePos = Vector3Add(position, Vector3(0, height/2, 0.045));
    auto wirelessNetworkInterface = new InterfaceWireless(wirelessNetworkInterfacePos, graphics, this->id, 1.5f, this);
    attachedDevices.push_back(wirelessNetworkInterface);
    DeviceManager::addInterface(wirelessNetworkInterface);
    this->wirelessInterface = wirelessNetworkInterface;

    Vector3 wiredNetworkInterfacePos = Vector3Add(position, Vector3(0, height/2, -0.045));
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

Vector3* Robot::getCurrCheckpoint() {
    if (movementCheckpoints.empty())
        return nullptr;
    return &movementCheckpoints.front();
}

Vector3* Robot::updateAndGetCurrCheckpoint() {
    Vector3* currCheckPoint = getCurrCheckpoint();
    if (currCheckPoint == nullptr)
        return nullptr;

    float distance = Vector3Distance(position, *currCheckPoint);
    if (distance < 0.1) {
        completeCheckpoint();
        currCheckPoint = getCurrCheckpoint();
    }
    return currCheckPoint;
}

void Robot::move() {
    Vector3* currCheckPoint = updateAndGetCurrCheckpoint();
    if (currCheckPoint == nullptr)
        return;

    Vector3 newPos = Vector3MoveTowards(position, *currCheckPoint, 0.01);
    Vector3 dV = Vector3Subtract(newPos, position);
    DeviceMovable::move(dV);
}

void Robot::snapToGround() {
    DeviceMovable::snapToGround();
    Device::move(Vector3(0, height / 2, 0));
}

void Robot::completeCheckpoint() {
    if (!movementCheckpoints.empty())
        movementCheckpoints.pop();
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
