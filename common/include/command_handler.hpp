#ifndef LCERF_COMMAND_HANDLER_HPP
#define LCERF_COMMAND_HANDLER_HPP

#include <string>
#include <unordered_map>

#include "command.hpp"
#include "command_event.hpp"

class CommandHandler {
private:
    std::unordered_map<std::string, CommandEvent> events;
    std::vector<CommandEvent> before;
    std::vector<CommandEvent> after;

public:
    CommandHandler();

    void on(const std::string& commandName, CommandEvent event);
    void alwaysBefore(const CommandEvent& event);
    void alwaysAfter(const CommandEvent& event);

    void execute(const std::string& command);
    void execute(const std::vector<std::string>& commands);
};


#endif //LCERF_COMMAND_HANDLER_HPP
