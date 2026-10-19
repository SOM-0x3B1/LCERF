#include "../../include/devices/device.hpp"
#include "raymath.h"

Device::Device(Vector3 position, Graphics* graphics) {
    this->id = -1;
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

void Device::moveTo(Vector3 pos) {
    Vector3 dV = Vector3Subtract(pos, position);
    Device::move(dV);
}

void Device::snapToGround() {
    float avgYBelow = cave->getMaxYValueInRectangle(
        position,
        Vector3(0, 0.4, 0),
        0.2,
        0.5,
        0.2);
    float dV = position.y - avgYBelow;
    move(Vector3(0, -dV, 0));
}

std::vector<Device *> Device::getAttachedInterfaces() {
    return attachedInterfaces;
}

void Device::assignID(int id) {
    this->id = id;
}

int Device::getID() {
    return id;
}

void Device::attachDevice(Device* device) {
    attachedDevices.push_back(device);
}

void Device::drawAttachedDevices() {
    for (auto device: attachedDevices) {
        device->draw3D();
    }
}

void Device::draw2D() { }

void Device::simulationStep() { }
