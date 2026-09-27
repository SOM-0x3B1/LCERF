#ifndef LCERF_INTERFACE_WIRED_HPP
#define LCERF_INTERFACE_WIRED_HPP
#include "interface.hpp"
#include "../../network/wire.hpp"

class ConnectedWire {
public:
    Wire* wire;
    bool isAttachedToSecondPosition;
};

class InterfaceWired : public Interface {
protected:
    std::vector<ConnectedWire> connectedWires;

public:
    explicit InterfaceWired(Vector3 position, Graphics* graphics, int id);
    explicit InterfaceWired(Vector3 position, Graphics* graphics, int id, Device* attachedTo);

    void connectNewWireToOtherInterface(InterfaceWired* interface);
    void connectExistingWireToOtherInterface(InterfaceWired* interface);
    void connectExistingWireToThisInterface(ConnectedWire connectedWire);
    void updatePosition(Vector3 newPosition) override;

    void updateConnections() override;

    void draw() override;
};


#endif //LCERF_INTERFACE_WIRED_HPP
