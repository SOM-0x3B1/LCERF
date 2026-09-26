#ifndef LCERF_INTERFACE_WIRELESS_HPP
#define LCERF_INTERFACE_WIRELESS_HPP
#include "interface.hpp"


class InterfaceWireless : public Interface{
private:
    std::vector<InterfaceWireless> connectedInterfaces;
    float range;

public:
    explicit InterfaceWireless(Vector3 position, Graphics* graphics, int id, float range);
    explicit InterfaceWireless(Vector3 position, Graphics* graphics, int id, float range, Device* attachedTo);

    void updateConnections() override;

    void draw() override;
};


#endif //LCERF_INTERFACE_WIRELESS_HPP
