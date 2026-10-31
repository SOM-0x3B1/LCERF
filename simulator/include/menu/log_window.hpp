#ifndef LCERF_LOG_WINDOW_HPP
#define LCERF_LOG_WINDOW_HPP

#include <deque>
#include <string>

#include "menu_window.hpp"

class LogWindow : public MenuWindow {
private:
    int fontSize;
    std::deque<std::string> logs;

public:
    explicit LogWindow(Graphics* g);

    void addLog(const std::string& log);

    void draw() override;
};

#endif //LCERF_LOG_WINDOW_HPP
