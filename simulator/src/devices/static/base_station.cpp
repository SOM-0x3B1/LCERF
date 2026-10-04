#include "../../../include/devices/static/base_station.hpp"

#include "raymath.h"
#include "../../../include/device_manager.hpp"
#include "../../../include/devices/attachable/interface_wireless.hpp"

BaseStation::BaseStation(Vector3 position, Graphics* graphics) : DeviceStatic(position, graphics) {
    supportPoints.push_back(this->position);

    Vector3 apPos = Vector3Add(position, Vector3(0, height, 0));
    auto wirelessAP = new InterfaceWireless(apPos, graphics, this->id, 2);
    this->attachedDevices.push_back(wirelessAP);
    DeviceManager::addInterface(wirelessAP);
    this->wirelessInterface = wirelessAP;

    Vector3 wiredNetworkInterfacePos = Vector3Add(position, Vector3(0, height, -0.1));
    auto wiredNetworkInterface = new InterfaceWired(wiredNetworkInterfacePos, graphics, this->id, this);
    attachedDevices.push_back(wiredNetworkInterface);
    DeviceManager::addInterface(wiredNetworkInterface);
    this->wiredInterface = wiredNetworkInterface;
}

InterfaceWired* BaseStation::getWiredInterface() {
    return wiredInterface;
}

void BaseStation::draw() {
    DrawCylinderWires(position, radius, radius, height, 8, GREEN);
    //DrawLine3D(position, Vector3Add(position, Vector3(0, 3, 0)), GREEN);
    DrawCylinderWires(position, 0.02, 0.02, 5, 3, GREEN);

    drawAttachedDevices();
}
