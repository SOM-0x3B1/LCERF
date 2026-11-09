#ifndef LCERF_SIMULATION_NETWORK_INTERFACE_HPP
#define LCERF_SIMULATION_NETWORK_INTERFACE_HPP

#include <chrono>
#include <string>
#include <queue>

class ExternalNetworkInterface {
    unsigned __int64 serverSocket;
    unsigned __int64 clientSocket;
    std::chrono::time_point<std::chrono::steady_clock> lastTriedConnection;
    bool connected;

    constexpr static int receiveBufferLen = 255;
    char receiveBuffer[receiveBufferLen]{};

    std::queue<std::string> rx{};
    std::queue<std::string> tx{};
    std::string receiveDataFromSocket();
    void sendDataToSocket(std::string data);

public:
    ExternalNetworkInterface();
    ~ExternalNetworkInterface();

    bool isConnected();

    void listenOnPort(int port);

    void tryAcceptConnection();

    void simulationStep();
    std::string receiveData();
    void sendData(std::string data);
};


#endif //LCERF_SIMULATION_NETWORK_INTERFACE_HPP
