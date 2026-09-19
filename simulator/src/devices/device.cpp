#include "../../include/devices/device.hpp"

Device::Device(Vector3 position, Graphics* graphics) {
    this->position = position;
    this->graphics = graphics;
}

Vector3 Device::getPosition() {
    return position;
}
