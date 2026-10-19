#include <cstdio>
#include <random>

#include "../../common/include/command.hpp"
#include "../include/network_interface.hpp"
#include "external/glfw/src/internal.h"

int main() {
    std::printf("Hello word!\n");

    auto networkInterface = NetworkInterface();
    networkInterface.init("127.0.0.1", 33222);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    Sleep(2000);
    while (true) {
        if (networkInterface.isConnected()) {
            float x = dist(mt);
            float y = dist(mt);
            networkInterface.sendData(CommandRobotMoveToPosition(rand() % 3, x, y).toString());
        }
        else {
            networkInterface.tryConnect();
        }
        Sleep(1000);
    }
}
