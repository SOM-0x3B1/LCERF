#ifndef LCERF_NETWORK_DATA_HPP
#define LCERF_NETWORK_DATA_HPP
#include <string>


class NetworkData {
public:
    int senderID;
    int targetID;
    std::string message;

    NetworkData(int senderID, int targetID, const std::string& message);

    NetworkData(int senderID, const std::string& message);
};


#endif //LCERF_NETWORK_DATA_HPP
