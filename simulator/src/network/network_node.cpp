#include "../../include/network/network_node.hpp"

NetworkNode::NetworkNode(int id) {
    this->id = id;
    this->connectedDevice = nullptr;
}

NetworkNode::NetworkNode(int id, Device* connectedDevice) {
    this->id = id;
    this->connectedDevice = connectedDevice;
}

std::vector<NetworkNode*> NetworkNode::getConnections() {
    return connections;
}

void NetworkNode::addConnection(NetworkNode* node) {
    connections.push_back(node);
}

void NetworkNode::addConnections(const std::vector<NetworkNode*>& nodes) {
    this->connections.append_range(nodes);
}

void NetworkNode::clearConnections() {
    this->connections.clear();
}

void NetworkNode::checkConnectionTo() {

}
