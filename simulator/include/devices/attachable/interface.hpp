#ifndef LCERF_INTERFACE_HPP
#define LCERF_INTERFACE_HPP
#include <queue>
#include <string>

#include "../device.hpp"
#include "../device_attachable.hpp"
#include "../../network/network_data.hpp"


enum class InterfaceType {
    WIRED,
    WIRELESS
};

class Interface : public DeviceAttachable {
protected:
    int id;
    Device* attachedTo;
    std::vector<Interface*> connectedInterfaces;

    std::deque<NetworkData> rxBuffer;

    bool isTargetInterfaceConnected(int targetID);

public:
    explicit Interface(Vector3 position, Graphics* graphics, int id);
    explicit Interface(Vector3 position, Graphics* graphics, int id, Device* attachedTo);

    virtual void updatePosition(Vector3 newPosition);
    virtual void updateConnections(std::vector<Interface*> interfaces) = 0;

    void addDataToRXBuffer(const NetworkData& data);
    void sendData(int targetID, std::string message);
    void broadCastData(std::string message);
    void getReceivedData();
};


#endif //LCERF_INTERFACE_HPP
