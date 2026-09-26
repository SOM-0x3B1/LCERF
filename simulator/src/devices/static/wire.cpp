//
// Created by somad on 2026-09-15.
//

#include "../../../include/devices/static/wire.hpp"

Wire::Wire(Vector3 startPosition, Vector3 endPosition, Graphics* graphics) : DeviceStatic(startPosition, graphics) {
    this->secondPosition = endPosition;
}

Vector3 Wire::getStartPosition() {
    return this->position;
}

Vector3 Wire::getEndPosition() {
    return this->secondPosition;
}

void Wire::setStartPosition(Vector3 pos) {
    this->position = pos;
}

void Wire::setEndPosition(Vector3 pos) {
    this->secondPosition = pos;
}

void Wire::draw() {
    DrawLine3D(position, secondPosition, GREEN);
}
