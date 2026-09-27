#include "../../include/devices/device.hpp"

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

void Device::attachDevice(Device* device) {
    attachedDevices.push_back(device);
}

void Device::drawAttachedDevices() {
    for (auto device: attachedDevices) {
        device->draw();
    }
}
