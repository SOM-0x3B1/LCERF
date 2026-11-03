#include <utility>

#include "../include/command_event.hpp"

CommandEvent::CommandEvent() {
    event = [](const std::vector<std::string>&){};
}

CommandEvent::CommandEvent(std::function<void(std::vector<std::string> commandParts)> event) {
    this->event = std::move(event);
}

void CommandEvent::execute(std::vector<std::string> commandParts) {
    event(std::move(commandParts));
}
