#include <cstdio>

#include "../include/network_interface.hpp"

int main() {
    std::printf("Hello word!\n");

    auto interface = NetworkInterface();
    interface.connectTo(33222);
}