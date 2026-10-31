#include "../../include/menu/log_window.hpp"

LogWindow::LogWindow(Graphics* g) : MenuWindow(g) {
    width = 300;
    height = 200;
    fontSize = 15;
}

void LogWindow::addLog(const std::string& log) {
    logs.push_back(log);
}

void LogWindow::draw() {
    int sh = graphics->getScreenHeight();
    DrawRectangle(10, sh - height - 10, width, height, defaultBackgroundColor);
    int logsSize = logs.size();
    int displayableLogCount = std::min(height / (fontSize + 10), logsSize) - 1;
    for (int i = 0; i < displayableLogCount; ++i) {
        DrawText(logs[logsSize - i - 1].c_str(), 20, sh - height - 10 + (displayableLogCount - i) * (fontSize + 10), fontSize, WHITE);
    }
}
