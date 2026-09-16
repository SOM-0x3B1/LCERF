//
// Created by somad on 2026-09-15.
//

#include "../../../include/devices/static/wire.hpp"

Wire::Wire(Vector3 startPosition, Vector3 endPosition) : DeviceStatic(startPosition) {
    this->endPosition = endPosition;
}

Vector3 Wire::getEndPosition() {
    return this->endPosition;
}

void Wire::draw() {
    DrawLine3D(position, endPosition, GREEN);
}
