#include <cstdio>
#include <random>

#include "../include/controller.hpp"
#include "../include/network_interface.hpp"
#include "../include/robot_manager.hpp"

int main() {
    auto networkInterface = NetworkInterface();
    networkInterface.init("127.0.0.1", 33222);

    RobotManager robotManager(&networkInterface);

    auto controller = Controller(&robotManager, &networkInterface);
    controller.run();
}