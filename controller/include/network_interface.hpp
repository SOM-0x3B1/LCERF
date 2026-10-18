#ifndef LCERF_SIMULATION_NETWORK_INTERFACE_HPP
#define LCERF_SIMULATION_NETWORK_INTERFACE_HPP

#include <string>

class NetworkInterface {
    unsigned int connectSocket;
    int serverPort;
    std::string serverIP;
    bool connected;

    constexpr static int receiveBufferLen = 255;
    char receiveBuffer[receiveBufferLen]{};

public:
    NetworkInterface();
    ~NetworkInterface();

    bool isConnected();

    void init(std::string ip, int port);
    void tryConnect();

    std::string receiveData();
    void sendData(std::string data);
};


#endif //LCERF_SIMULATION_NETWORK_INTERFACE_HPP
