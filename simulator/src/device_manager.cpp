#include "../include/device_manager.hpp"

#include "../include/devices/attachable/interface.hpp"

std::vector<Device*> DeviceManager::devices;
std::vector<Interface*> DeviceManager::interfaces;

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

void DeviceManager::drawAll() {
    for (auto device: devices) {
        device->draw();
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

void DeviceManager::addInterface(Interface *interface) {
    interfaces.push_back(interface);
}

void DeviceManager::updateInterfaces() {
    for (auto interface: interfaces) {
        interface->updateConnections();
    }
}

std::vector<Device*>* DeviceManager::getDeviceCollection() {
    return &devices;
}

std::vector<Interface*>* DeviceManager::getInterfaceCollection() {
    return &interfaces;
}
