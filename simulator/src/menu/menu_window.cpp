#include "../../include/menu/menu_window.hpp"

Color MenuWindow::defaultBackgroundColor = Color(0, 0, 0, 180);

MenuWindow::MenuWindow(Graphics* graphics) {
    this->graphics = graphics;
}