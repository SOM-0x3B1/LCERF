#include "../../include/devices/device.hpp"
#include "raymath.h"

Device::Device(Vector3 position, Graphics* graphics) {
    id = -1;
    this->position = position;
    this->graphics = graphics;
    this->cave = nullptr;
}

Device::~Device() {
    for (auto device: attachedDevices) {
        delete device;
    }
}

void Device::setCave(Cave* newCave) {
    this->cave = newCave;
}

std::vector<Vector3> Device::getPointsBelow(Vector3 point) {
    const float maxDepth = 0.5;
    const float searchAreaLength = 0.2;

    Chunk* mainChunk = cave->getChunkAt(point);
    std::vector<Vector3>* mainPoints = mainChunk->getPoints();
    int mainPointCount = mainPoints->size();

    auto pointsInSearchArea = std::vector<Vector3>();
    for (int i = 0; i < mainPointCount; ++i) {
        Vector3 currPoint = (*mainPoints)[i];
        if (currPoint.y < point.y && currPoint.y > point.y - maxDepth &&
            currPoint.x < point.x + searchAreaLength && currPoint.x > point.x - searchAreaLength &&
            currPoint.z < point.z + searchAreaLength && currPoint.z > point.z - searchAreaLength)
        {
            pointsInSearchArea.push_back(currPoint);
        }
    }
    return pointsInSearchArea;
}

float Device::getDistanceFromGround(Vector3 point) {
    float avgYBelow = cave->getMaxYValueInRectangle(
        position,
        Vector3(0, 0.4, 0),
        0.2,
        0.5,
        0.2);
    return point.y - avgYBelow;
}

Vector3 Device::getPosition() {
    return position;
}

void Device::move(Vector3 dV) {
    this->position = Vector3Add(position, dV);
    for (auto attachment : attachedDevices) {
        attachment->move(dV);
    }
}

void Device::snapToGround() {
    /*float maxY = -9999;
    for (auto pos : supportPoints) {
        auto ray = Ray(pos, Vector3(0, -1, 0));
        RayCollision collision = cave->getRayCollision(ray);
        float y = collision.point.y;
        if (y > maxY) {
            maxY = y;
        }
    }
    auto newPos = this->position;
    newPos.y = maxY;
    move(Vector3Subtract(newPos, position));*/

    /*auto points = getPointsBelow(supportPoints[0]);

    if (points.size() > 0) {
        auto newPos = this->position;

        float ySum = 0.0f;
        for (auto element: points) {
            ySum += element.y;
        }
        newPos.y = ySum / points.size();
        move(Vector3Subtract(newPos, position));
    }*/

    float dV = getDistanceFromGround(position);
    move(Vector3(0, -dV, 0));
}

void Device::attachDevice(Device* device) {
    attachedDevices.push_back(device);
}

void Device::drawAttachedDevices() {
    for (auto device: attachedDevices) {
        device->draw();
    }
}

void Device::simulationStep() { }
