#ifndef LCERF_SIDE_MENU_HPP
#define LCERF_SIDE_MENU_HPP

#include <vector>
#include "../graphics.hpp"
#include "menu_content.hpp"
#include "menu_window.hpp"

class SideMenu : public MenuWindow {
private:
    int width;
    bool enabled;
    std::vector<MenuContent> layout;
    std::vector<MenuContent> options;
    int selectedOptionIndex;

public:
    explicit SideMenu(Graphics* graphics);

    bool toggle();
    bool isEnabled();
    void stepDownSelectedOption();
    void stepUpSelectedOption();
    void select();

    void draw() override;
};


#endif //LCERF_SIDE_MENU_HPP
