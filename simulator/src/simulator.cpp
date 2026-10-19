#include "../include/simulator.hpp"

#include <random>

Simulator::Simulator(Cave* cave, DeviceManager* deviceManager, Graphics* graphics) {
    this->cave = cave;
    this->deviceManager = deviceManager;
    this->graphics = graphics;
}

Cave* Simulator::getCave() {
    return cave;
}

DeviceManager* Simulator::getDeviceManager() {
    return deviceManager;
}

Graphics* Simulator::getGraphics() {
    return graphics;
}

void Simulator::init() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    auto baseStation = new BaseStation(Vector3(0, 0.2, 0), graphics);
    deviceManager->addStaticDevice(baseStation);
    deviceManager->setBaseStation(baseStation);

    for (int i = 0; i < 3; i++) {
        Vector3 robotPosition = {.x = dist(mt), .y = 0.1, .z = dist(mt)};
        auto robot = new Robot(robotPosition, graphics);
        deviceManager->addRobot(robot);
    }

    auto devices = *deviceManager->getDeviceCollection();
    for (auto device: devices) {
        device->setCave(cave);
        device->snapToGround();
    }

    deviceManager->registerInterfaces();
    deviceManager->assignIDs();
}

void Simulator::step() {
    auto devices = *deviceManager->getDeviceCollection();
    for (auto device: devices) {
        device->simulationStep();
    }
    deviceManager->handleControllerCommand();
}
