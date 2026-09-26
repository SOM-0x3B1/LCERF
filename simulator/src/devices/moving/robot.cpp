#include "../../../include/devices/moving/robot.hpp"

#include "../../../../cmake-build-release-visual-studio/_deps/raylib-src/src/raymath.h"
#include "../../../include/devices/attachable/interface_wireless.hpp"

Robot::Robot(Vector3 position, Graphics* graphics) : DeviceMovable(position, graphics) {
    Vector3 wirelessNetworkInterfacePos = Vector3Add(position, Vector3(0, 0.05, 0.1));
    auto wirelessNetworkInterface = new InterfaceWireless(wirelessNetworkInterfacePos, graphics, 1, 0.8f); // TODO: add ID
    attachedDevices.push_back(wirelessNetworkInterface);
}

void Robot::draw() {
    DrawCube(position, 0.15, 0.1, 0.2, YELLOW);
    for (auto device: attachedDevices) {
        device->draw();
    }
}
