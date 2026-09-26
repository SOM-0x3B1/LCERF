#include "../../../include/devices/attachable/interface_wired.hpp"

InterfaceWired::InterfaceWired(Vector3 position, Graphics *graphics, int id)
: Interface(position, graphics, id) {
}

InterfaceWired::InterfaceWired(Vector3 position, Graphics *graphics, int id, Device *attachedTo)
: Interface(position, graphics, id, attachedTo){
}

void InterfaceWired::addWire(Wire *wire, bool isAttachedToSecondPosition) {
    auto connectedWire = ConnectedWire(wire, isAttachedToSecondPosition);
    connectedWires.push_back(connectedWire);
}

void InterfaceWired::updatePosition(Vector3 newPosition) {
    Interface::updatePosition(newPosition);

    for (auto connectedWire: connectedWires) {
        Wire* wire = connectedWire.wire;
        if (connectedWire.isAttachedToSecondPosition)
            wire->setEndPosition(this->position);
        else
            wire->setStartPosition(this->position);
    }
}

void InterfaceWired::updateConnections() {
}

void InterfaceWired::draw() {
    DrawCube(position, 0.2, 0.1, 0.1, GREEN);
}
