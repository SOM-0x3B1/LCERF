#ifndef LCERF_NETWORK_NODE_HPP
#define LCERF_NETWORK_NODE_HPP
#include <vector>

#include "../devices/device.hpp"


class NetworkNode {
private:
    int id;
    Device* connectedDevice;
    std::vector<NetworkNode*> connections;

public:
    explicit NetworkNode(int id);
    explicit NetworkNode(int id, Device* connectedDevice);

    std::vector<NetworkNode*> getConnections();
    void addConnection(NetworkNode* node);
    void addConnections(const std::vector<NetworkNode*>& nodes);
    void clearConnections();

    void checkConnectionTo();
};


#endif //LCERF_NETWORK_NODE_HPP
