#ifndef LCERF_CONTROLLER_HPP
#define LCERF_CONTROLLER_HPP

#include "robot_manager.hpp"
#include "../../common/include/command_handler.hpp"

class Controller {
private:
    RobotManager* robotManager;
    NetworkInterface* networkInterface;
    CommandHandler commandHandler;

    void registerCommands();

public:
    explicit Controller(RobotManager* robotManager, NetworkInterface* networkInterface);

    void run();
};


#endif //LCERF_CONTROLLER_HPP
