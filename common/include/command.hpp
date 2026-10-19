#ifndef LCERF_COMMANDS_HPP
#define LCERF_COMMANDS_HPP

#include <string>
#include <vector>

class Command {
protected:
    std::string name;

public:
    explicit Command(std::string name);
    virtual ~Command() = default;

    virtual std::string toString();

    static std::vector<std::string> split(std::string s);
};

class CommandRobotMoveToPosition : public  Command{
protected:
    int id;
    float x;
    float y;

public:
    explicit CommandRobotMoveToPosition(int id, float x, float y);

    std::string toString() override;
};

#endif //LCERF_COMMANDS_HPP
