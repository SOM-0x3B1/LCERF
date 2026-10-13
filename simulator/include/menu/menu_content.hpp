#ifndef LCERF_MENU_CONTENT_HPP
#define LCERF_MENU_CONTENT_HPP

#include <string>

enum class OptionActionType {DO_NOTHING, NAVIGATE, FUNCTION};
enum class MenuContentType {TITLE, LABEL, OPTION};

class OptionAction {
private:
    OptionActionType type;
    std::string navigateTo;
    void (*function)();

public:
    OptionAction();
    explicit OptionAction(std::string navigateTo);
    explicit OptionAction(void (*function)());

    std::string execute();
};

class MenuContent {
public:
    explicit MenuContent(MenuContentType type, std::string text);

    MenuContentType type;
    std::string text;
    OptionAction action;
};

#endif //LCERF_MENU_CONTENT_HPP
