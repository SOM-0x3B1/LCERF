#ifndef LCERF_COMMAND_EVENT_HPP
#define LCERF_COMMAND_EVENT_HPP

#include <functional>
#include <string>

class CommandEvent {
private:
    std::function<void(std::vector<std::string> commandParts)> event;

public:
    CommandEvent();
    explicit CommandEvent(std::function<void(std::vector<std::string> commandParts)> event);

    void execute(std::vector<std::string> commandParts);
};


#endif //LCERF_COMMAND_EVENT_HPP
