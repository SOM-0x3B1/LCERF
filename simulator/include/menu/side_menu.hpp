#ifndef LCERF_SIDE_MENU_HPP
#define LCERF_SIDE_MENU_HPP

#include <string>
#include <vector>
#include "menu_window.hpp"

enum class ContentType {TITLE, LABEL, OPTION};

class Content {
public:
    explicit Content(ContentType type, std::string text);

    ContentType type;
    std::string text;
};

class SideMenu : MenuWindow {
private:
    int width;
    bool enabled;
    std::vector<Content> layout;
    std::vector<Content> options;
    int selectedOptionIndex;

public:
    explicit SideMenu(Graphics* graphics);

    bool toggle();
    bool isEnabled();
    void stepDownSelectedOption();
    void stepUpSelectedOption();

    void draw() override;
};


#endif //LCERF_SIDE_MENU_HPP
