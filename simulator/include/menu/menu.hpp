#ifndef LCERF_MENU_HPP
#define LCERF_MENU_HPP

#include <map>
#include <unordered_map>
#include <vector>
#include "side_menu.hpp"

class SideMenuWithSubMenus {
private:
    SideMenu* sideMenu;
    SideMenuWithSubMenus* parent;
    std::unordered_map<std::string, SideMenuWithSubMenus*> subSideMenus;

public:
    explicit SideMenuWithSubMenus(SideMenu* sideMenu);
    ~SideMenuWithSubMenus();

    void setParent(SideMenuWithSubMenus* parent);
    SideMenuWithSubMenus* getParent();

    SideMenu* getMainSideMenu();
    SideMenuWithSubMenus* getSubSideMenu(const std::string& key);
    void addSubSideMenu(const std::string& name, SideMenuWithSubMenus* sideMenu);
};

class Menu {
private:
    bool enabled;
    SideMenuWithSubMenus mainSideMenu;
    SideMenuWithSubMenus* currSideMenu;

    SideMenuWithSubMenus* navigateToPath(const std::vector<std::string> &path);

public:
    explicit Menu(Graphics* graphics);

    SideMenu* getCurrentSideMenu();

    void addSectionToMainSideMenu(MenuContent* content);
    void addSectionToMainSideMenu(std::vector<MenuContent*> layout);
    void addSubSideMenu(const std::vector<std::string>& path, const std::string& name, SideMenuWithSubMenus* sideMenu);

    bool toggle();
    bool isEnabled();
    void select();
    void back();

    void draw();
};


#endif //LCERF_MENU_HPP