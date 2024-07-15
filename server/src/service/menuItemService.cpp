#include"../../inc/service/menuItemService.h"

MenuItemService::MenuItemService(std::unique_ptr<IMenuItemDAO> menuItemDAO)
    : menuItemDAO(std::move(menuItemDAO)) {}

bool MenuItemService::addMenuItem(const MenuItem& menuItem) {
    return menuItemDAO->addMenuItem(menuItem);
}

bool MenuItemService::updateMenuItem(const MenuItem& menuItem) {
    return menuItemDAO->updateMenuItem(menuItem);
}

MenuItem MenuItemService::deleteMenuItemById(int menuItemId) {
    return menuItemDAO->deleteMenuItem(menuItemId);
}

MenuItem MenuItemService::getMenuItemById(int menuItemId) {
    return menuItemDAO->getMenuItemById(menuItemId);
}

std::vector<MenuItem> MenuItemService::getAllMenuItems() {
    return menuItemDAO->getAllMenuItems();
}


