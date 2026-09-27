#include "../../../include/devices/attachable/interface.hpp"

bool Interface::isTargetInterfaceConnected(int targetID) {
    return false;
}

Interface::Interface(Vector3 position, Graphics* graphics, int id)
: DeviceAttachable(position, graphics) {
    this->id = id;
    this->attachedTo = nullptr;
}

Interface::Interface(Vector3 position, Graphics* graphics, int id, Device *attachedTo)
: DeviceAttachable(position, graphics) {
    this->id = id;
    this->attachedTo = attachedTo;
}

void Interface::updatePosition(Vector3 newPosition) {
    this->position = newPosition;
}


void Interface::addDataToRXBuffer(const NetworkData& data) {
    this->rxBuffer.push_back(data);
}

void Interface::sendData(int targetID, std::string message) {

}

void Interface::broadCastData(std::string message) {

}

void Interface::getReceivedData() {

}
