#ifndef LCERF_SIMULATION_NETWORK_INTERFACE_HPP
#define LCERF_SIMULATION_NETWORK_INTERFACE_HPP

#include <string>

class NetworkInterface {
    unsigned int connectSocket;
    bool connected;

    constexpr static int receiveBufferLen = 255;
    char receiveBuffer[receiveBufferLen]{};

public:
    NetworkInterface();
    ~NetworkInterface();

    bool isConnected();

    void connectTo(int port);

    std::string receiveData();
};


#endif //LCERF_SIMULATION_NETWORK_INTERFACE_HPP
