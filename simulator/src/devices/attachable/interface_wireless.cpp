#include "../../../include/devices/attachable/interface_wireless.hpp"

InterfaceWireless::InterfaceWireless(Vector3 position, Graphics *graphics, int id, float range)
: Interface(position, graphics, id) {
    this->range = range;
}

InterfaceWireless::InterfaceWireless(Vector3 position, Graphics *graphics, int id, float range, Device *attachedTo)
: Interface(position, graphics, id, attachedTo){
    this->range = range;
}

void InterfaceWireless::updateConnections() {
}

void InterfaceWireless::draw() {
    DrawCube(position, 0.08, 0.05, 0.1, GREEN);
    DrawSphereWires(position, range, 10, 10, Color(0, 0, 255, 50));
}
