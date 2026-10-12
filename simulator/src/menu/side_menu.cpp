#include <utility>

#include "../../include/menu/side_menu.hpp"

#include "raylib.h"

Content::Content(ContentType type, std::string text) {
    this->type = type;
    this->text = std::move(text);
}

SideMenu::SideMenu(Graphics* graphics) : MenuWindow(graphics) {
    width = 300;
    enabled = false;
    selectedOptionIndex = 0;

    layout.push_back(Content(ContentType::TITLE, "LCERF Menu"));
    layout.push_back(Content(ContentType::LABEL, "Navigate"));
    layout.push_back(Content(ContentType::OPTION, "Device management"));
    layout.push_back(Content(ContentType::OPTION, "Simulator actions"));
    layout.push_back(Content(ContentType::OPTION, "Options"));

    for (auto element : layout) {
        if (element.type == ContentType::OPTION)
            options.push_back(element);
    }
}

bool SideMenu::toggle() {
    enabled = !enabled;
    return enabled;
}

bool SideMenu::isEnabled() {
    return enabled;
}

void SideMenu::stepDownSelectedOption() {
    selectedOptionIndex++;
    if (selectedOptionIndex > options.size() - 1)
        selectedOptionIndex = 0;
}

void SideMenu::stepUpSelectedOption() {
    selectedOptionIndex--;
    if (selectedOptionIndex < 0)
        selectedOptionIndex = options.size() - 1;
}

void SideMenu::draw() {
    if (enabled) {
        int sw = graphics->getScreenWidth();
        int sh = graphics->getScreenHeight();
        DrawRectangle(sw - width, 0, width, sh, Color(255, 255, 255, 180));

        int startX = sw - width + 10;
        int currY = 10;
        int elementCount = layout.size();
        int currOption = 0;

        for (int i = 0; i < elementCount; ++i) {
            Content element = layout[i];
            switch (element.type) {
                case ContentType::TITLE:
                    DrawText(element.text.c_str(), startX, currY, 36, BLACK);
                    DrawLineEx(Vector2(startX, currY + 44), Vector2(sw - 10, currY + 44), 3.0f, BLACK);
                    currY += 60;
                    break;
                case ContentType::LABEL:
                    DrawText(element.text.c_str(), startX + 10, currY, 30, BLACK);
                    currY += 40;
                    break;
            case ContentType::OPTION:
                    Color color = (currOption == selectedOptionIndex ? BLUE : BLACK);
                    DrawText("-", startX + 20, currY, 26, color);
                    DrawText(element.text.c_str(), startX + 40, currY, 26, color);
                    currY += 36;
                    currOption++;
                    break;
            }
        }
    }
}
