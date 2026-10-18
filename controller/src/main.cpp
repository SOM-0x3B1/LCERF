#include <cstdio>

#include "../include/network_interface.hpp"
#include "external/glfw/src/internal.h"

int main() {
    std::printf("Hello word!\n");

    auto networkInterface = NetworkInterface();
    networkInterface.init("127.0.0.1", 33222);

    for (int i = 0; true; i++) {
        if (networkInterface.isConnected()) {
            networkInterface.sendData("asd123-");
            networkInterface.sendData(std::to_string(i));
        }
        else {
            networkInterface.tryConnect();
        }
        Sleep(500);
    }
}
