#ifndef LCERF_BASE_STATION_HPP
#define LCERF_BASE_STATION_HPP

#include "../device_static.hpp"
#include "../attachable/interface_wired.hpp"
#include "../attachable/interface_wireless.hpp"


class BaseStation : public DeviceStatic {
    const float radius = 0.3f;
    const float height = 0.1f;

    InterfaceWired* wiredInterface;
    InterfaceWireless* wirelessInterface;

public:
    explicit BaseStation(Vector3 position, Graphics* graphics);

    InterfaceWired* getWiredInterface();

    void draw() override;
};


#endif //LCERF_BASE_STATION_HPP
