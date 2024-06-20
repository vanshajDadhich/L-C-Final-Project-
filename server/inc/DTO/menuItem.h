#pragma once

#include <string>

enum MenuItemType : int { Breakfast = 1, Lunch = 2, Dinner = 3 };

struct MenuItem {
  int menuItemId;
  std::string menuItemName;
  MenuItemType menuItemType;
  bool availability;    
  int price;
  MenuItem(int menuItemId, std::string menuItemName, int menuItemType,
       bool availability, int price)
      : menuItemId(menuItemId),menuItemName(menuItemName), menuItemType(static_cast<MenuItemType>(menuItemType)), price(price), availability(availability) {}
};