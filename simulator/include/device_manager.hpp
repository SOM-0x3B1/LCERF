#ifndef LCERF_DEVICE_MANAGER_H
#define LCERF_DEVICE_MANAGER_H

#include <vector>
#include "devices/device.hpp"
#include "robot_manager.hpp"
#include "../../common/include/command_handler.hpp"
#include "devices/device_static.hpp"
#include "devices/attachable/interface.hpp"
#include "devices/static/base_station.hpp"
#include "menu/menu.hpp"

class DeviceManager {
private:
    Graphics* graphics;
    Menu* menu;
    SideMenuWithSubMenus* sideMenus;
    LogWindow* logWindow{};
    SimulationNetworkInterface* controllerInterface;
    CommandHandler commandHandler;

    Device* selectedDevice;
    std::vector<Device*> devices;
    std::vector<Interface*> interfaces;
    RobotManager robotManager;

    BaseStation* baseStation;

public:
    explicit DeviceManager(Graphics* graphics, Menu* menu, SimulationNetworkInterface* controllerInterface);

    void registerMenus();
    void registerCommands();

    SimulationNetworkInterface* getControllerInterface();

    void drawAll3D();
    void drawAll2D();

    void addRobot(Robot* robot);
    void addStaticDevice(DeviceStatic* device);
    void setBaseStation(BaseStation* station);
    std::vector<Device*>* getDeviceCollection();
    void assignIDs();
    void registerRobots();

    void selectDevice(int index);
    void deselectDevice();
    void focusCameraOnSelectedDevice();

    void registerInterfaces();
    void updateInterfaces();
    void handleControllerCommands();

    std::vector<Interface*>* getInterfaceCollection();
};


#endif //LCERF_DEVICE_MANAGER_H
