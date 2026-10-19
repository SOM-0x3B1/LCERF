#ifndef LCERF_DEVICE_MANAGER_H
#define LCERF_DEVICE_MANAGER_H

#include <vector>
#include "devices/device.hpp"
#include "robot_manager.hpp"
#include "devices/device_static.hpp"
#include "devices/attachable/interface.hpp"
#include "devices/static/base_station.hpp"
#include "menu/menu.hpp"

class DeviceManager {
private:
    Graphics* graphics;
    Menu* menu;
    SideMenuWithSubMenus* sideMenus;

    Device* selectedDevice;
    static std::vector<Device*> devices;
    static std::vector<Interface*> interfaces;
    RobotManager robotManager;

    BaseStation* baseStation;

public:
    explicit DeviceManager(Graphics* graphics, Menu* menu);

    void registerMenus();

    void drawAll3D();
    void drawAll2D();

    void addRobot(Robot* robot);
    void addStaticDevice(DeviceStatic* device);
    void setBaseStation(BaseStation* station);

    void selectDevice(int index);
    void deselectDevice();
    void focusCameraOnSelectedDevice();

    static void addInterface(Interface* interface);
    static void updateInterfaces();
    static std::vector<Device*>* getDeviceCollection();
    static std::vector<Interface*>* getInterfaceCollection();
};


#endif //LCERF_DEVICE_MANAGER_H
