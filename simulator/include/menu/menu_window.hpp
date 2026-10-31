#ifndef LCERF_MENU_WINDOW_HPP
#define LCERF_MENU_WINDOW_HPP

#include "../graphics.hpp"

class MenuWindow {
protected:
    int width;
    int height;
    Graphics* graphics;
    static Color defaultBackgroundColor;

public:
    explicit MenuWindow(Graphics* graphics);
    virtual ~MenuWindow() = default;
    virtual void draw() = 0;
};


#endif //LCERF_MENU_WINDOW_HPP
