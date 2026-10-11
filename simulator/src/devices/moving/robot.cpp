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

    auto robotPosition = Vector2(position.x, position.z);
    for (int i = 0; i < 400; i++) {
        robotPosition = Vector2Add(robotPosition, Vector2(dist(mt), dist(mt)));
        movementCheckpoints.push(robotPosition);
    }

    stuckForTicks = 0;
}

void Robot::moveTowardsCheckpoint() {
    Vector2* currCheckPoint = updateAndGetCurrCheckpoint();
    if (currCheckPoint == nullptr)
        return;

    auto prevPos3D = position;
    auto prevPos2D = Vector2(prevPos3D.x, prevPos3D.z);

    Vector2 newPos2D = Vector2MoveTowards(prevPos2D, *currCheckPoint, 0.01);
    Vector3 newPos3D = Vector3(newPos2D.x, prevPos3D.y, newPos2D.y);

    float newY = cave->getMaxYValueInRectangle(
        newPos3D,
        {0, 0, 0},
        width + 0.1f,
        height + 0.1f,
        length + 0.1f);

    if (abs(newY - prevPos3D.y) > (stuckForTicks > 10 ? 0.06 : 0.03)) {
        completeCheckpoint();
        stuckForTicks++;
    }
    else {
        Vector2 dV = Vector2Subtract(newPos2D, prevPos2D);
        move(Vector3(dV.x, newY - prevPos3D.y, dV.y));
        stuckForTicks = 0;
    }
}

float Robot::distanceFromCheckpoint(Vector2 p) {
    return Vector2Distance(Vector2(position.x, position.z), p);
}

Vector2* Robot::getCurrCheckpoint() {
    if (movementCheckpoints.empty())
        return nullptr;
    return &movementCheckpoints.front();
}

Vector2* Robot::updateAndGetCurrCheckpoint() {
    Vector2* currCheckPoint = getCurrCheckpoint();
    if (currCheckPoint == nullptr)
        return nullptr;

    float distance = distanceFromCheckpoint(*currCheckPoint);
    if (distance < 0.01) {
        completeCheckpoint();
        currCheckPoint = getCurrCheckpoint();
    }
    return currCheckPoint;
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
    moveTowardsCheckpoint();
}