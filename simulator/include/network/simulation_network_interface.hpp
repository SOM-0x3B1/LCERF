#ifndef LCERF_SIMULATION_NETWORK_INTERFACE_HPP
#define LCERF_SIMULATION_NETWORK_INTERFACE_HPP

#include <chrono>
#include <string>

class SimulationNetworkInterface {
    unsigned int serverSocket;
    unsigned int clientSocket;
    std::chrono::time_point<std::chrono::steady_clock> lastTriedConnection;
    bool connected;

    constexpr static int receiveBufferLen = 255;
    char receiveBuffer[receiveBufferLen]{};

public:
    SimulationNetworkInterface();
    ~SimulationNetworkInterface();

    bool isConnected();

    void listenOnPort(int port);

    void tryAcceptConnection();

    std::string receiveData();
};


#endif //LCERF_SIMULATION_NETWORK_INTERFACE_HPP
