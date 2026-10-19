#include "../../include/menu/side_menu.hpp"

#include "raylib.h"

SideMenu::SideMenu(Graphics* graphics) : MenuWindow(graphics) {
    width = 350;
    selectedOptionIndex = 0;
}

void SideMenu::addToLayout(MenuContent* content) {
    this->layout.push_back(content);
    if (content->getType() == MenuContentType::OPTION)
        options.push_back(content);
}

void SideMenu::addToLayout(std::vector<MenuContent*> layout) {
    this->layout.append_range(layout);
    for (auto element: layout) {
        if (element->getType() == MenuContentType::OPTION)
            options.push_back(element);
    }
}

void SideMenu::resetSelection() {
    selectedOptionIndex = 0;
}

void SideMenu::stepDownSelectedOption() {
    selectedOptionIndex++;
    if (selectedOptionIndex > options.size())
        selectedOptionIndex = 0;
}

void SideMenu::stepUpSelectedOption() {
    selectedOptionIndex--;
    if (selectedOptionIndex < 0)
        selectedOptionIndex = options.size();
}

std::vector<std::string> SideMenu::select() {
    if (selectedOptionIndex < options.size()) {
        return options[selectedOptionIndex]->select();
    }
    else {
        selectedOptionIndex = 0;
        return {".."};
    }
}

void SideMenu::draw() {
    int sw = graphics->getScreenWidth();
    int sh = graphics->getScreenHeight();
    DrawRectangle(sw - width, 0, width, sh, Color(0, 0, 0, 180));
    //DrawLineEx(Vector2(sw - width, 0), Vector2(sw - width, sh), 3.0f, WHITE);

    int startX = sw - width + 10;
    int currY = 10;
    int elementCount = layout.size();
    int currOptionIndex = 0;

    for (int i = 0; i < elementCount; ++i) {
        MenuContent* element = layout[i];
        switch (element->getType()) {
            case MenuContentType::TITLE:
                DrawText(element->getText().c_str(), startX, currY, 30, WHITE);
                DrawLineEx(Vector2(startX, currY + 44), Vector2(sw - 10, currY + 44), 3.0f, WHITE);
                currY += 60;
                break;
            case MenuContentType::LABEL:
                DrawText(element->getText().c_str(), startX + 10, currY, 24, WHITE);
                currY += 40;
                break;
            case MenuContentType::OPTION:
                Color color = (currOptionIndex == selectedOptionIndex ? BLUE : WHITE);
                DrawText("-", startX + 12, currY, 26, color);
                DrawText(element->getText().c_str(), startX + 40, currY, 20, color);
                currY += 26;
                currOptionIndex++;
                break;
        }
    }
    Color color = (selectedOptionIndex == options.size() ? BLUE : WHITE);
    DrawText("-", startX + 10, sh - 40, 26, color);
    DrawText("Back", startX + 30, sh - 40, 26, color);
}
