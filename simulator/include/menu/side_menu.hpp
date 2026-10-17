#ifndef LCERF_SIDE_MENU_HPP
#define LCERF_SIDE_MENU_HPP

#include <vector>
#include "../graphics.hpp"
#include "menu_content.hpp"
#include "menu_window.hpp"

class SideMenu : public MenuWindow {
private:
    int width;
    std::vector<MenuContent*> layout;
    std::vector<MenuContent*> options;
    int selectedOptionIndex;

public:
    explicit SideMenu(Graphics* graphics);

    void addToLayout(MenuContent* content);
    void addToLayout(std::vector<MenuContent*> layout);

    void resetSelection();
    void stepDownSelectedOption();
    void stepUpSelectedOption();
    std::vector<std::string> select();

    void draw() override;
};


#endif //LCERF_SIDE_MENU_HPP
