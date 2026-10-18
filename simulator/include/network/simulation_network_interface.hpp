#ifndef LCERF_SIMULATION_NETWORK_INTERFACE_HPP
#define LCERF_SIMULATION_NETWORK_INTERFACE_HPP

#include <string>

class SimulationNetworkInterface {
    unsigned int serverSocket;
    unsigned int clientSocket;
    bool connected;

    constexpr static int receiveBufferLen = 255;
    char receiveBuffer[receiveBufferLen]{};

public:
    SimulationNetworkInterface();
    ~SimulationNetworkInterface();

    bool isConencted();

    void listenOnPort(int port);

    void tryAcceptConnection();

    std::string receiveData();
};


#endif //LCERF_SIMULATION_NETWORK_INTERFACE_HPP
