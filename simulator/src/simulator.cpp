#include "../include/simulator.hpp"

Simulator::Simulator(Cave* cave, DeviceManager* deviceManager) {
    this->cave = cave;
    this->deviceManager = deviceManager;
}

void Simulator::step() {
    auto devices = *DeviceManager::getDeviceCollection();
    for (auto device: devices) {
        device->simulationStep();
    }
}
