#include "../../../include/devices/static/base_station.hpp"

#include <chrono>

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

    controllerInterface.listenOnPort(33222);
}

InterfaceWired* BaseStation::getWiredInterface() {
    return wiredInterface;
}

void BaseStation::simulationStep() {
    if (!controllerInterface.isConnected()) {
        controllerInterface.tryAcceptConnection();
    }
    else {
        controllerInterface.simulationStep();
        std::string received = controllerInterface.receiveData();
        if (received.empty()) {
            return;
        }
        wiredInterface->sendData(1, received);
        wirelessInterface->sendData(1, received);
    }
}

void BaseStation::draw3D() {
    DrawCylinderWires(position, radius, radius, height, 8, GREEN);
    //DrawLine3D(position, Vector3Add(position, Vector3(0, 3, 0)), GREEN);
    Color color = controllerInterface.isConnected() ? GREEN : RED;
    DrawCylinderWires(position, 0.02, 0.02, 5, 3, color);

    drawAttachedDevices();
}

void BaseStation::draw2D() {
    if (controllerInterface.isConnected()) {
        DrawText("CONTROLLER CONNECTED", 10, 33, 20, GREEN);
    }
    else {
        DrawText("CONTROLLER DISCONNECTED", 10, 33, 24, RED);
    }
}
