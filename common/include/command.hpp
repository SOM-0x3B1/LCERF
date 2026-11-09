#ifndef LCERF_COMMANDS_HPP
#define LCERF_COMMANDS_HPP

#include <string>
#include <vector>

#define COMMAND_ROBOT_REGISTER "RR"
#define COMMAND_ROBOT_REGISTER_FINISH "RRF"
#define COMMAND_ROBOT_MOVE_TO_POS "RMP"
#define COMMAND_ROBOT_WAYPOINT_COMPLETE "RWPC"
#define COMMAND_ROBOT_STUCK "RS"

class Command {
protected:
    std::string name;

    static std::vector<std::string> splitString(std::string s, char delimiter);


public:
    explicit Command(std::string name);
    virtual ~Command() = default;

    std::string getName();

    virtual std::string toString();

    static std::vector<std::string> splitCommands(std::string s);
    static std::vector<std::string> split(std::string s);
};

class CommandRobotRegister : public Command{
protected:
    int id;

public:
    explicit CommandRobotRegister(int id);

    int getID();

    std::string toString() override;
    static CommandRobotRegister parse(std::vector<std::string> parts);
};

class CommandRobotRegisterFinish : public Command{
public:
    explicit CommandRobotRegisterFinish();

    std::string toString() override;
};

class CommandRobotMoveToPosition : public Command{
protected:
    int id;
    float x;
    float y;

public:
    explicit CommandRobotMoveToPosition(int id, float x, float y);

    int getID();
    float getX();
    float getY();

    std::string toString() override;
    static CommandRobotMoveToPosition parse(std::vector<std::string> parts);
};

class CommandRobotWaypointComplete : public Command{
protected:
    int id;

public:
    explicit CommandRobotWaypointComplete(int id);

    int getID();

    std::string toString() override;
    static CommandRobotWaypointComplete parse(std::vector<std::string> parts);
};

class CommandRobotStuck : public Command{
protected:
    int id;

public:
    explicit CommandRobotStuck(int id);

    int getID();

    std::string toString() override;
    static CommandRobotStuck parse(std::vector<std::string> parts);
};

#endif //LCERF_COMMANDS_HPP
