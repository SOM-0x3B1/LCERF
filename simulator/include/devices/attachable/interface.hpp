#ifndef LCERF_INTERFACE_HPP
#define LCERF_INTERFACE_HPP
#include <queue>
#include <string>

#include "../device.hpp"
#include "../device_attachable.hpp"
#include "../../network/network_data.hpp"
#include "../../network/network_node.hpp"


class Interface : public DeviceAttachable {
protected:
    int id;
    Device* attachedTo;
    NetworkNode networkNode;
    std::deque<NetworkData> rxBuffer;

    bool isTargetInterfaceConnected(int targetID);

public:
    explicit Interface(Vector3 position, Graphics* graphics, int id);
    explicit Interface(Vector3 position, Graphics* graphics, int id, Device* attachedTo);

    virtual void updatePosition(Vector3 newPosition);
    virtual void updateConnections() = 0;

    void addDataToRXBuffer(const NetworkData& data);
    void sendData(int targetID, std::string message);
    void broadCastData(std::string message);
    void getReceivedData();
};


#endif //LCERF_INTERFACE_HPP
