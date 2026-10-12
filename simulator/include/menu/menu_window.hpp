#ifndef LCERF_MENU_HPP
#define LCERF_MENU_HPP
#include "../graphics.hpp"


class MenuWindow {
protected:
    Graphics* graphics;

public:
    explicit MenuWindow(Graphics* graphics);
    virtual ~MenuWindow() = default;
    virtual void draw() = 0;
};


#endif //LCERF_MENU_HPP
