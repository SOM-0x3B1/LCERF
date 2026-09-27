#include "../../include/network/wire.hpp"

Wire::Wire(Vector3 firstPosition, Vector3 secondPosition, Graphics* graphics) {
    this->firstPosition = firstPosition;
    this->secondPosition = secondPosition;
    this->firstConnectedTo = nullptr;
    this->secondConnectedTo = nullptr;
    this->graphics = graphics;
}

Wire::Wire(Interface *firstInterface, Interface *secondInterface, Graphics *graphics) {
    this->firstConnectedTo = nullptr;
    this->secondConnectedTo = nullptr;
    setFirstConnectedTo(firstInterface);
    setSecondConnectedTo(secondInterface);
    this->graphics = graphics;
}

Vector3 Wire::getFirstPosition() {
    return this->firstPosition;
}

Vector3 Wire::getSecondPosition() {
    return this->secondPosition;
}

Interface* Wire::getFirstConnectedTo() {
    return firstConnectedTo;
}

Interface* Wire::getSecondConnectedTo() {
    return secondConnectedTo;
}

void Wire::setFirstPosition(Vector3 pos) {
    this->firstPosition = pos;
}

void Wire::setSecondPosition(Vector3 pos) {
    this->secondPosition = pos;
}

void Wire::setFirstConnectedTo(Interface *connectedTo) {
    firstConnectedTo = connectedTo;
    setFirstPosition(connectedTo->getPosition());
}

void Wire::setSecondConnectedTo(Interface *connectedTo) {
    secondConnectedTo = connectedTo;
    setSecondPosition(connectedTo->getPosition());
}

void Wire::draw() {
    DrawLine3D(firstPosition, secondPosition, GREEN);
}
