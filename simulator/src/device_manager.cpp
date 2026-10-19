#include "../include/device_manager.hpp"

#include "../../common/include/command.hpp"
#include "../include/devices/attachable/interface.hpp"

DeviceManager::DeviceManager(Graphics* graphics, Menu* menu) : robotManager(graphics, menu) {
    this->menu = menu;
    this->graphics = graphics;
    this->selectedDevice = nullptr;
    this->baseStation = nullptr;
    this->sideMenus = nullptr;

    registerMenus();
}

void DeviceManager::registerMenus() {
    menu->addSectionToMainSideMenu(std::vector{
        new MenuContent(MenuContentType::OPTION, "Device manager",
            new OptionActionNavigation({"device_manager"})),
    });

    auto sideMenu = new SideMenu(graphics);
    sideMenu->addToLayout(std::vector{
        new MenuContent(MenuContentType::TITLE, "Device manager"),
        new MenuContent(MenuContentType::LABEL, "Generic"),
        new MenuContent(MenuContentType::OPTION, "Add device to base"),
        new MenuContent(MenuContentType::OPTION, "Edit device",
            new OptionActionNavigation({"edit_device"})),
        new MenuContent(MenuContentType::OPTION, "Disable wireless comm."),
    });
    this->sideMenus = new SideMenuWithSubMenus(sideMenu);
    menu->addSubSideMenu({}, "device_manager", this->sideMenus);

    sideMenu = new SideMenu(graphics);
    sideMenu->addToLayout(std::vector{
        new MenuContent(MenuContentType::TITLE, "Edit device"),
        new MenuContent(MenuContentType::OPTION, "asd"),
        new MenuContent(MenuContentType::OPTION, "sdfsd"),
        new MenuContent(MenuContentType::OPTION, "fghfgh"),
    });
    auto editDeviceMenu = new SideMenuWithSubMenus(sideMenu);
    menu->addSubSideMenu({"device_manager"}, "edit_device", editDeviceMenu);
}

void DeviceManager::drawAll3D() {
    for (auto device: devices) {
        device->draw3D();
    }
}

void DeviceManager::drawAll2D() {
    for (auto device: devices) {
        device->draw2D();
    }
}

void DeviceManager::addRobot(Robot* robot) {
    devices.push_back(robot);
    robotManager.addRobot(robot);
    robot->connectNewWireTo(baseStation->getWiredInterface());

    int currentRobotIndex = devices.size() - 1;
    robotManager.getSideMenus()->getMainSideMenu()->addToLayout(
        new MenuContent(
            MenuContentType::OPTION,
            "Robot name",
            new OptionActionFunction([this, currentRobotIndex](){selectDevice(currentRobotIndex);})
        )
    );
}

void DeviceManager::addStaticDevice(DeviceStatic *device) {
    devices.push_back(device);
}

void DeviceManager::setBaseStation(BaseStation* station) {
    this->baseStation = station;
}

void DeviceManager::selectDevice(int index) {
    selectedDevice = devices[index];
}

void DeviceManager::deselectDevice() {
    selectedDevice = nullptr;
}

void DeviceManager::focusCameraOnSelectedDevice() {
    if (selectedDevice != nullptr) {
        graphics->moveTargetToPos(selectedDevice->getPosition());
    }
}

void DeviceManager::registerInterfaces() {
    for (auto device: devices) {
        auto devInterfaces = device->getAttachedInterfaces();
        for (auto interface: devInterfaces) {
            this->interfaces.push_back(dynamic_cast<Interface*>(interface));
        }
    }
}

void DeviceManager::updateInterfaces() {
    for (auto interface: interfaces) {
        interface->updateConnections(&interfaces);
    }
}

void DeviceManager::handleControllerCommand() {
    std::string data = baseStation->receiveData();
    if (!data.empty()) {
        std::vector<std::string> parts = Command::split(data);
        if (parts[0] == "RMP") {
            int id = std::stoi(parts[1]);
            auto pos = Vector2(std::stof(parts[2]), std::stof(parts[3]));
            robotManager.getRobotByID(id)->addWaypoint(pos);
        }
    }
}

std::vector<Device*>* DeviceManager::getDeviceCollection() {
    return &devices;
}

std::vector<Interface*>* DeviceManager::getInterfaceCollection() {
    return &interfaces;
}

void DeviceManager::assignIDs() {
    int size = interfaces.size();
    for (int i = 0; i < size; ++i) {
        interfaces[i]->assignID(i + 1);
    }
}