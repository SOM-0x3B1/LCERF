#include <utility>

#include "../include/command.hpp"

Command::Command(std::string name) : name(std::move(name)) { }

std::string Command::toString() {
    return name;
}

std::vector<std::string> Command::split(std::string s) {
    std::vector<std::string> parts;
    size_t pos = 0;
    while ((pos = s.find(';')) != std::string::npos) {
        std::string part = s.substr(0, pos);
        parts.push_back(part);
        s.erase(0, pos + 1);
    }
    parts.push_back(s);
    return parts;
}

CommandRobotMoveToPosition::CommandRobotMoveToPosition(int id, float x, float y)
    : Command("RMP"), id(id), x(x), y(y) { }

std::string CommandRobotMoveToPosition::toString() {
    std::string res = name + ";";
    res += std::to_string(id) + ";";
    res += std::to_string(x) + ";";
    res += std::to_string(y);
    return res;
}