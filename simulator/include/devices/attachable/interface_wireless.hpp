#ifndef LCERF_INTERFACE_WIRELESS_HPP
#define LCERF_INTERFACE_WIRELESS_HPP
#include "interface.hpp"


class InterfaceWireless : public Interface{
private:
    float range;

    bool isInterfaceConnected(Interface* interface);

public:
    explicit InterfaceWireless(Vector3 position, Graphics* graphics, int id, float range);
    explicit InterfaceWireless(Vector3 position, Graphics* graphics, int id, float range, Device* attachedTo);

    float getRange();

    void updateConnections(std::vector<Interface*> interfaces) override;

    void draw() override;
};


#endif //LCERF_INTERFACE_WIRELESS_HPP
