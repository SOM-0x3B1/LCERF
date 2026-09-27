#include "../../../include/devices/attachable/interface_wired.hpp"

InterfaceWired::InterfaceWired(Vector3 position, Graphics *graphics, int id)
: Interface(position, graphics, id) {
}

InterfaceWired::InterfaceWired(Vector3 position, Graphics *graphics, int id, Device *attachedTo)
: Interface(position, graphics, id, attachedTo){
}

void InterfaceWired::connectNewWireToOtherInterface(InterfaceWired* interface) {
    Wire* newWire = new Wire(this, interface, graphics);
    auto cwire = ConnectedWire(newWire, false);
    this->connectedWires.push_back(cwire);
    interface->connectExistingWireToThisInterface(cwire);
}

void InterfaceWired::connectExistingWireToOtherInterface(InterfaceWired *interface) {

}

void InterfaceWired::connectExistingWireToThisInterface(ConnectedWire connectedWire) {
    connectedWire.isAttachedToSecondPosition = !connectedWire.isAttachedToSecondPosition;
    this->connectedWires.push_back(connectedWire);
}

void InterfaceWired::updatePosition(Vector3 newPosition) {
    Interface::updatePosition(newPosition);

    for (auto connectedWire: connectedWires) {
        Wire* wire = connectedWire.wire;
        if (connectedWire.isAttachedToSecondPosition)
            wire->setSecondPosition(this->position);
        else
            wire->setFirstPosition(this->position);
    }
}

void InterfaceWired::updateConnections() {
    for (auto [wire, isAttachedToSecondPosition]: connectedWires) {
        Interface* connectedInterface;
        if (isAttachedToSecondPosition)
            connectedInterface = wire->getSecondConnectedTo();
        else
            connectedInterface = wire->getFirstConnectedTo();
        if (connectedInterface != this)
            connectedInterfaces.push_back(connectedInterface);
    }
}

void InterfaceWired::draw() {
    DrawCube(position, 0.2, 0.1, 0.1, BLUE);
    for (auto cWire: connectedWires) {
        if (cWire.isAttachedToSecondPosition)
            cWire.wire->draw();
    }
}
