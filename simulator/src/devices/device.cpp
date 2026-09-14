#include "../../include/devices/device.hpp"

Device::Device(Vector3 position) {
    this->position = position;
}

Vector3 Device::getPosition() {
    return position;
}
