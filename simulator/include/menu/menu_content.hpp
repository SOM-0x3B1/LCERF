#ifndef LCERF_MENU_CONTENT_HPP
#define LCERF_MENU_CONTENT_HPP

#include <functional>
#include <string>
#include <vector>

enum class MenuContentType {TITLE, LABEL, OPTION};

class OptionAction {
public:
    virtual ~OptionAction() = default;

    virtual std::vector<std::string> execute() = 0;
};

class OptionActionFunction : public OptionAction {
private:
    std::function<void()> function;

public:
    explicit OptionActionFunction(std::function<void()> func);

    std::vector<std::string> execute() override;
};

class OptionActionNavigation : public OptionAction {
private:
    std::vector<std::string> navigateTo;

public:
    explicit OptionActionNavigation(std::vector<std::string> navigateToPath);

    std::vector<std::string> execute() override;
};

class MenuContent {
    MenuContentType type;
    std::string text;
    OptionAction* action;

public:
    explicit MenuContent(MenuContentType type, std::string text);
    MenuContent(MenuContentType type, std::string text, OptionAction *action);

    ~MenuContent();

    MenuContentType getType();
    std::string getText();

    std::vector<std::string> select();
};

#endif //LCERF_MENU_CONTENT_HPP
