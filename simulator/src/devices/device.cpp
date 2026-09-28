#include "../../include/devices/device.hpp"
#include "raymath.h"

Device::Device(Vector3 position, Graphics* graphics) {
    id = -1;
    this->position = position;
    this->graphics = graphics;
}

Device::~Device() {
    for (auto device: attachedDevices) {
        delete device;
    }
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


void Device::attachDevice(Device* device) {
    attachedDevices.push_back(device);
}

void Device::drawAttachedDevices() {
    for (auto device: attachedDevices) {
        device->draw();
    }
}

void Device::simulationStep() { }
