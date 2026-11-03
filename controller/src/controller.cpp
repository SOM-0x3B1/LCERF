#include "../include/controller.hpp"
#include "../../common/include/command.hpp"

#include <thread>

void Controller::registerCommands() {
    commandHandler.on(
        COMMAND_ROBOT_REGISTER,
        CommandEvent([this](const std::vector<std::string>& commandParts) {
            auto cmd = CommandRobotRegister::parse(commandParts);
            robotManager->registerRobot(cmd.getID());
        }));

    commandHandler.on(
        COMMAND_ROBOT_REGISTER_FINISH,
        CommandEvent([this](const std::vector<std::string>& commandParts) {
            robotManager->finishRegistration();
        }));

    commandHandler.on(
        COMMAND_ROBOT_WAYPOINT_COMPLETE,
        CommandEvent([this](const std::vector<std::string>& commandParts) {
            auto cmd = CommandRobotWaypointComplete::parse(commandParts);
            robotManager->completeWaypoint(cmd.getID());
        }));
}

Controller::Controller(RobotManager *robotManager, NetworkInterface *networkInterface) {
    this->robotManager = robotManager;
    this->networkInterface = networkInterface;

    registerCommands();
}

void Controller::run() {
    while (true) {
        if (networkInterface->isConnected()) {
            if (robotManager->isReady()) {
                robotManager->updateRobots();
            }

            std::string received = networkInterface->receiveData();
            auto commands = Command::splitCommands(received);
            commandHandler.execute(commands);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        else {
            networkInterface->tryConnect();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}
