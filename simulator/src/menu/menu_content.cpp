#include <utility>

#include "../../include/menu/menu_content.hpp"

OptionAction::OptionAction() {
    this->type = OptionActionType::DO_NOTHING;
    this->navigateTo = "";
    this->function = nullptr;
}

OptionAction::OptionAction(std::string navigateTo) {
    this->type = OptionActionType::NAVIGATE;
    this->navigateTo = std::move(navigateTo);
    this->function = nullptr;
}

OptionAction::OptionAction(void(*function)()) {
    this->type = OptionActionType::FUNCTION;
    this->navigateTo = "";
    this->function = function;
}

std::string OptionAction::execute() {
    switch (type) {
        case OptionActionType::NAVIGATE:
            return navigateTo;
        case OptionActionType::FUNCTION:
            function();
            return "";
        default:
            return "";
    }
}

MenuContent::MenuContent(MenuContentType type, std::string text) {
    this->type = type;
    this->text = std::move(text);
}
