#include"../../inc/service/menuItemService.h"

MenuItemService::MenuItemService(IMenuItemDAO* menuItemDAO)
    : menuItemDAO(menuItemDAO) {}

bool MenuItemService::addMenuItem(const MenuItem& menuItem) {
    return menuItemDAO->addMenuItem(menuItem);
}

bool MenuItemService::updateMenuItem(const MenuItem& menuItem) {
    return menuItemDAO->updateMenuItem(menuItem);
}

MenuItem MenuItemService::deleteMenuItemByID(int menuItemId) {
    return menuItemDAO->deleteMenuItem(menuItemId);
}

MenuItem MenuItemService::getMenuItemById(int menuItemId) {
    return menuItemDAO->getMenuItemByID(menuItemId);
}

std::vector<MenuItem> MenuItemService::getAllMenuItems() {
    return menuItemDAO->getAllMenuItems();
}


