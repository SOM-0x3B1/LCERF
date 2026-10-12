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
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    auto robotPosition = Vector2(position.x, position.z);
    for (int i = 0; i < 40; i++) {
        robotPosition = Vector2Add(robotPosition, Vector2(dist(mt) - 0.5f, dist(mt)));
        movementWaypoints.push_back(robotPosition);
    }

    stuckForTicks = 0;
    showWaypoints = true;
}

void Robot::moveTowardsWaypoint() {
    Vector2* currWaypoint = updateAndGetCurrWaypoint();
    if (currWaypoint == nullptr)
        return;

    auto prevPos3D = position;
    auto prevPos2D = Vector2(prevPos3D.x, prevPos3D.z);

    Vector2 newPos2D = Vector2MoveTowards(prevPos2D, *currWaypoint, 0.01);
    Vector3 newPos3D = Vector3(newPos2D.x, prevPos3D.y, newPos2D.y);

    float newY = cave->getMaxYValueInRectangle(
        newPos3D,
        {0, 0, 0},
        width + 0.1f,
        height + 0.1f,
        length + 0.1f);

    if (abs(newY - prevPos3D.y) > (stuckForTicks > 10 ? 0.06 : 0.05)) {
        stuckForTicks++;
        if (stuckForTicks > 20) {
            completeWaypoint();
            moveTo(Vector3(0, 0.1, 0));
            snapToGround();
        }
    }
    else {
        Vector2 dV = Vector2Subtract(newPos2D, prevPos2D);
        move(Vector3(dV.x, newY - prevPos3D.y, dV.y));
        stuckForTicks = 0;
    }

    showWaypoints = true;
}

float Robot::distanceFromWaypoint(Vector2 p) {
    return Vector2Distance(Vector2(position.x, position.z), p);
}

Vector2* Robot::getCurrWaypoint() {
    if (movementWaypoints.empty())
        return nullptr;
    return &movementWaypoints.front();
}

Vector2* Robot::updateAndGetCurrWaypoint() {
    Vector2* currWaypoint = getCurrWaypoint();
    if (currWaypoint == nullptr)
        return nullptr;

    float distance = distanceFromWaypoint(*currWaypoint);
    if (distance < 0.01) {
        completeWaypoint();
        currWaypoint = getCurrWaypoint();
    }
    return currWaypoint;
}

void Robot::snapToGround() {
    DeviceMovable::snapToGround();
    Device::move(Vector3(0, height / 2, 0));
}

void Robot::completeWaypoint() {
    if (!movementWaypoints.empty())
        movementWaypoints.pop_front();
}

void Robot::connectNewWireTo(InterfaceWired *interface) {
    wiredInterface->connectNewWireToOtherInterface(interface);
}

void Robot::draw() {
    DrawCube(position, 0.15, 0.1, 0.2, YELLOW);
    drawAttachedDevices();

    Vector3 currPoint = position;
    if (showWaypoints) {
        for (auto waypoint: movementWaypoints) {
            auto newPoint = Vector3(waypoint.x, 0, waypoint.y);
            DrawLine3D(currPoint, newPoint, RED);
            DrawSphere(newPoint, 0.05, RED);
            currPoint = newPoint;
        }
    }
}

void Robot::simulationStep() {
    moveTowardsWaypoint();
}