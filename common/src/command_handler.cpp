#include <utility>

#include "../include/command_handler.hpp"

CommandHandler::CommandHandler() = default;

void CommandHandler::on(const std::string& commandName, CommandEvent event) {
    events[commandName] = std::move(event);
}

void CommandHandler::alwaysBefore(const CommandEvent& event) {
    before.push_back(event);
}

void CommandHandler::alwaysAfter(const CommandEvent& event) {
    after.push_back(event);
}

void CommandHandler::execute(const std::string& command) {
    if (!command.empty()) {
        std::vector<std::string> commandParts = Command::split(command);

        for (auto beforeEvent: before) {
            beforeEvent.execute(commandParts);
        }

        events[commandParts[0]].execute(commandParts);

        for (auto afterEvent: after) {
            afterEvent.execute(commandParts);
        }
    }
}

void CommandHandler::execute(const std::vector<std::string>& commands) {
    for (const auto& command: commands) {
        execute(command);
    }
}
