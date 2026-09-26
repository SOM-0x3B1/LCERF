#include "../../include/devices/device.hpp"

Device::Device(Vector3 position, Graphics* graphics) {
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
