#include <utility>

#include "../include/command.hpp"

std::vector<std::string> Command::splitString(std::string s, char delimiter) {
    std::vector<std::string> parts;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        std::string part = s.substr(0, pos);
        parts.push_back(part);
        s.erase(0, pos + 1);
    }
    parts.push_back(s);
    return parts;
}

Command::Command(std::string name) : name(std::move(name)) { }

std::string Command::getName() {
    return name;
}

std::string Command::toString() {
    return name;
}

std::vector<std::string> Command::splitCommands(std::string s) {
    return splitString(std::move(s), '\n');
}

std::vector<std::string> Command::split(std::string s) {
    return splitString(std::move(s), ';');
}

CommandRobotRegister::CommandRobotRegister(int id)
    : Command(COMMAND_ROBOT_REGISTER), id(id) { }

int CommandRobotRegister::getID() {
    return id;
}

std::string CommandRobotRegister::toString() {
    std::string res = name + ";";
    res += std::to_string(id) + "\n";
    return res;
}

CommandRobotRegister CommandRobotRegister::parse(std::vector<std::string> parts) {
    return CommandRobotRegister(std::stoi(parts[1]));
}

CommandRobotRegisterFinish::CommandRobotRegisterFinish()
    : Command(COMMAND_ROBOT_REGISTER_FINISH) { }

std::string CommandRobotRegisterFinish::toString() {
    return name + "\n";
}

CommandRobotMoveToPosition::CommandRobotMoveToPosition(int id, float x, float y)
    : Command(COMMAND_ROBOT_MOVE_TO_POS), id(id), x(x), y(y) { }

int CommandRobotMoveToPosition::getID() {
    return id;
}

float CommandRobotMoveToPosition::getX() {
    return x;
}

float CommandRobotMoveToPosition::getY() {
    return y;
}

std::string CommandRobotMoveToPosition::toString() {
    std::string res = name + ";";
    res += std::to_string(id) + ";";
    res += std::to_string(x) + ";";
    res += std::to_string(y) + "\n";
    return res;
}

CommandRobotMoveToPosition CommandRobotMoveToPosition::parse(std::vector<std::string> parts) {
    return CommandRobotMoveToPosition(
        std::stoi(parts[1]),
        std::stof(parts[2]),
        std::stof(parts[3]));
}

CommandRobotWaypointComplete::CommandRobotWaypointComplete(int id)
    : Command(COMMAND_ROBOT_WAYPOINT_COMPLETE), id(id) { }

int CommandRobotWaypointComplete::getID() {
    return id;
}

std::string CommandRobotWaypointComplete::toString() {
    std::string res = name + ";";
    res += std::to_string(id) + "\n";
    return res;
}

CommandRobotWaypointComplete CommandRobotWaypointComplete::parse(std::vector<std::string> parts) {
    return CommandRobotWaypointComplete(std::stoi(parts[1]));
}

CommandRobotStuck::CommandRobotStuck(int id)
    : Command(COMMAND_ROBOT_STUCK), id(id) { }

int CommandRobotStuck::getID() {
    return id;
}

std::string CommandRobotStuck::toString() {
    std::string res = name + ";";
    res += std::to_string(id) + "\n";
    return res;
}

CommandRobotStuck CommandRobotStuck::parse(std::vector<std::string> parts) {
    return CommandRobotStuck(std::stoi(parts[1]));
}
