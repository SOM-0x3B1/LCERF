#include "../include/device_manager.hpp"

#include "../../common/include/command.hpp"
#include "../include/devices/attachable/interface.hpp"

DeviceManager::DeviceManager(Graphics* graphics, Menu* menu, SimulationNetworkInterface* controllerInterface)
    : robotManager(graphics, menu, controllerInterface){
    this->menu = menu;
    this->graphics = graphics;
    this->controllerInterface = controllerInterface;

    this->selectedDevice = nullptr;
    this->baseStation = nullptr;
    this->sideMenus = nullptr;

    registerMenus();
    registerCommands();
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

    logWindow = new LogWindow(graphics);
    menu->addLogWindow(logWindow);
}

void DeviceManager::registerCommands() {
    commandHandler.alwaysAfter(
        CommandEvent([this](const std::vector<std::string> &commandParts) {
            std::string log;
            for (auto part: commandParts) {
                log.append(part);
                log.append(" | ");
            }
            logWindow->addLog(log);
        }));

    commandHandler.on(
        COMMAND_ROBOT_MOVE_TO_POS,
        CommandEvent([this](const std::vector<std::string>& commandParts) {
            auto cmd = CommandRobotMoveToPosition::parse(commandParts);
            auto pos = Vector2(cmd.getX(), cmd.getY());
            robotManager.getRobotByID(cmd.getID())->addWaypoint(pos);
        }));
}

SimulationNetworkInterface * DeviceManager::getControllerInterface() {
    return controllerInterface;
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

void DeviceManager::handleControllerCommands() {
    std::string data = controllerInterface->receiveData();
    if (!data.empty()) {
        auto commands = Command::splitCommands(data);
        commandHandler.execute(commands);
    }
}

std::vector<Device*>* DeviceManager::getDeviceCollection() {
    return &devices;
}

std::vector<Interface*>* DeviceManager::getInterfaceCollection() {
    return &interfaces;
}

// TODO: extend
void DeviceManager::assignIDs() {
    int size = interfaces.size();
    for (int i = 0; i < size; ++i) {
        interfaces[i]->assignID(i + 1);
    }
}

void DeviceManager::registerRobots() {
    robotManager.registerRobots();
}