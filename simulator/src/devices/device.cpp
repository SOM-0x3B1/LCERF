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
    float maxY = -9999;
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
    move(Vector3Subtract(newPos, position));
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
