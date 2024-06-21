#include"../../inc/service/menuItemService.h"

MenuItemService::MenuItemService(IMenuItemDAO* menuItemDAO)
    : menuItemDAO(menuItemDAO) {}

bool MenuItemService::addMenuItem(std::vector<std::string> menuData) {
    MenuItem menuItem(std::stoi(menuData[0]), menuData[1], std::stoi(menuData[2]), std::stoi(menuData[3]), std::stoi(menuData[4]));
    return menuItemDAO->addMenuItem(menuItem);
}

bool MenuItemService::updateMenuItem(const MenuItem& menuItem) {
    return menuItemDAO->updateMenuItem(menuItem);
}

bool MenuItemService::deleteMenuItemByID(int menuItemId) {
    return menuItemDAO->deleteMenuItem(menuItemId);
}

MenuItem MenuItemService::getMenuItemById(int menuItemId) {
    return menuItemDAO->getMenuItemByID(menuItemId);
}

std::vector<std::vector<std::string>> MenuItemService::getAllMenuItems() {
    std::vector<MenuItem> menuItems = menuItemDAO->getAllMenuItems();
    std::vector<std::vector<std::string>> menuItemsData;
    for (auto menuItem : menuItems) {
        std::vector<std::string> menuItems;
        menuItems.push_back(std::to_string(menuItem.menuItemId));
        menuItems.push_back(menuItem.menuItemName);
        menuItems.push_back(std::to_string(menuItem.menuItemType));
        menuItems.push_back(std::to_string(menuItem.availability));
        menuItems.push_back(std::to_string(menuItem.price));
        menuItemsData.push_back(menuItems); // Change the vector variable name here as well
    }
    return menuItemsData;
}


