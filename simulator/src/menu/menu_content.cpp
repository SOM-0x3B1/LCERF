#include <utility>
#include <vector>
#include "../../include/menu/menu_content.hpp"

OptionActionFunction::OptionActionFunction(std::function<void()>func) {
    this->function = std::move(func);
}

std::vector<std::string> OptionActionFunction::execute() {
    this->function();
    return {};
}

OptionActionNavigation::OptionActionNavigation(std::vector<std::string> navigateToPath) {
    this->navigateTo = std::move(navigateToPath);
}

std::vector<std::string> OptionActionNavigation::execute() {
    return navigateTo;
}

MenuContent::MenuContent(MenuContentType type, std::string text) {
    this->type = type;
    this->text = std::move(text);
    this->action = nullptr;
}

MenuContent::MenuContent(MenuContentType type, std::string text, OptionAction* action) {
    this->type = type;
    this->text = std::move(text);
    this->action = action;
}

MenuContent::~MenuContent() {
    delete action;
}

MenuContentType MenuContent::getType() {
    return type;
}

std::string MenuContent::getText() {
    return text;
}

std::vector<std::string> MenuContent::select() {
    if (action != nullptr)
        return action->execute();
    return {};
}
