#include <utility>

#include "../../include/menu/menu.hpp"


SideMenuWithSubMenus::SideMenuWithSubMenus(SideMenu *sideMenu) {
    this->sideMenu = sideMenu;
    this->subSideMenus = std::unordered_map<std::string, SideMenuWithSubMenus*>();
}



SideMenuWithSubMenus::~SideMenuWithSubMenus() {
    delete sideMenu;
    for (const auto& element: subSideMenus) {
        delete element.second;
    }
}

void SideMenuWithSubMenus::setParent(SideMenuWithSubMenus* parent) {
    this->parent = std::move(parent);
}

SideMenuWithSubMenus* SideMenuWithSubMenus::getParent() {
    return parent;
}

SideMenu* SideMenuWithSubMenus::getMainSideMenu() {
    return sideMenu;
}

SideMenuWithSubMenus* SideMenuWithSubMenus::getSubSideMenu(const std::string& key) {
    return subSideMenus[key];
}

void SideMenuWithSubMenus::addSubSideMenu(const std::string& name, SideMenuWithSubMenus *sideMenu) {
    sideMenu->setParent(this);
    subSideMenus[name] = sideMenu;
}

SideMenuWithSubMenus* Menu::navigateToPath(const std::vector<std::string>& path) {
    auto currMenu = currSideMenu;
    for (const auto& key : path) {
        if (key == "..") {
            if (currMenu->getParent() == currMenu) {
                enabled = false;
                return nullptr;
            }
            currMenu = currSideMenu->getParent();
        }
        else {
            currMenu = currMenu->getSubSideMenu(key);
            if (currMenu == nullptr) {
                return nullptr;
            }
        }
    }
    return currMenu;
}

Menu::Menu(Graphics* graphics) : mainSideMenu(new SideMenu(graphics)) {
    this->enabled = false;
    addSectionToMainSideMenu(std::vector{new MenuContent(MenuContentType::TITLE, "LCERF Menu")});
    this->currSideMenu = &mainSideMenu;
    mainSideMenu.setParent(&mainSideMenu);
}

SideMenu* Menu::getCurrentSideMenu() {
    return currSideMenu->getMainSideMenu();
}

void Menu::addSectionToMainSideMenu(MenuContent* content) {
    mainSideMenu.getMainSideMenu()->addToLayout(content);
}

void Menu::addSectionToMainSideMenu(std::vector<MenuContent*> layout) {
    mainSideMenu.getMainSideMenu()->addToLayout(std::move(layout));
}

void Menu::addSubSideMenu(const std::vector<std::string>& path, const std::string& name, SideMenuWithSubMenus* sideMenu) {
    auto currMenu = navigateToPath(path);
    currMenu->addSubSideMenu(name, sideMenu);
}

bool Menu::toggle() {
    enabled = !enabled;
    return enabled;
}

bool Menu::isEnabled() {
    return enabled;
}

void Menu::select() {
    std::vector<std::string> navigateTo = currSideMenu->getMainSideMenu()->select();
    if (!navigateTo.empty()) {
        SideMenuWithSubMenus* newMenu = navigateToPath(navigateTo);
        if (newMenu != nullptr)
            currSideMenu = newMenu;
    }
}

void Menu::back() {
    if (currSideMenu == &mainSideMenu) {
        enabled = false;
        mainSideMenu.getMainSideMenu()->resetSelection();
    }
    else {
        this->currSideMenu = currSideMenu->getParent();
    }
}

void Menu::draw() {
    if (enabled) {
        currSideMenu->getMainSideMenu()->draw();
    }
}

