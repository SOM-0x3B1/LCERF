#include "../../../include/devices/attachable/interface_wireless.hpp"

#include "raymath.h"
#include "../../../include/device_manager.hpp"

bool InterfaceWireless::isInterfaceConnected(Interface *interface) {
    auto wirelessInterface = dynamic_cast<InterfaceWireless*>(interface);
    if (wirelessInterface == nullptr)
        return false;

    float distance = Vector3Distance(this->position, wirelessInterface->getPosition());
    if (distance > this->range && distance > wirelessInterface->getRange())
        return false;

    return true;
}

InterfaceWireless::InterfaceWireless(Vector3 position, Graphics *graphics, int id, float range)
: Interface(position, graphics, id) {
    this->range = range;
}

InterfaceWireless::InterfaceWireless(Vector3 position, Graphics *graphics, int id, float range, Device *attachedTo)
: Interface(position, graphics, id, attachedTo){
    this->range = range;
}

float InterfaceWireless::getRange() {
    return range;
}

void InterfaceWireless::updateConnections() {
    connectedInterfaces.clear();
    std::vector<Interface*>* interfaces = DeviceManager::getInterfaceCollection();
    for (auto interface: *interfaces) {
        if (isInterfaceConnected(interface))
            connectedInterfaces.push_back(interface);
    }
}

void InterfaceWireless::draw() {
    DrawCube(position, 0.08, 0.05, 0.1, BLUE);
    if (graphics->getVectorDistanceFromTarget(position) <= range)
        DrawSphereWires(position, range, 10, 10, Color(0, 0, 255, 100));
    for (auto interface: connectedInterfaces) {
        DrawLine3D(position, interface->getPosition(), BLUE);
    }
}
