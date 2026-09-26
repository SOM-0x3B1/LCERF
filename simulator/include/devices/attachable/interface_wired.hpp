#ifndef LCERF_INTERFACE_WIRED_HPP
#define LCERF_INTERFACE_WIRED_HPP
#include "interface.hpp"
#include "../static/wire.hpp"

class ConnectedWire {
public:
    Wire* wire;
    bool isAttachedToSecondPosition;
};

class InterfaceWired : public Interface {
private:
    std::vector<ConnectedWire> connectedWires;

public:
    explicit InterfaceWired(Vector3 position, Graphics* graphics, int id);
    explicit InterfaceWired(Vector3 position, Graphics* graphics, int id, Device* attachedTo);

    void addWire(Wire* wire, bool isAttachedToSecondPosition);
    void updatePosition(Vector3 newPosition) override;
    void updateConnections() override;

    void draw() override;
};


#endif //LCERF_INTERFACE_WIRED_HPP
