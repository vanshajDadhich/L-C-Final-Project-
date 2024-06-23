#pragma once

#include <string>
#include <sstream>
#include "serializable.h"

enum MenuItemType : int { Breakfast = 1, Lunch = 2, Dinner = 3 };

struct MenuItem : public Serializable {
  int menuItemId = 0;
  std::string menuItemName;
  MenuItemType menuItemType;
  bool availability;
  int price;

  MenuItem(int menuItemId = 0, std::string menuItemName = "", int menuItemType = 0,
           bool availability = false, int price = 0)
      : menuItemId(menuItemId), menuItemName(menuItemName), 
        menuItemType(static_cast<MenuItemType>(menuItemType)), 
        availability(availability), price(price) {}

  // MenuItem() 
  //       : menuItemId(0), menuItemName(""), menuItemType(MenuItemType::Breakfast), availability(false), price(0) {}

  std::string serialize() const override {
    return std::to_string(menuItemId) + ";" +
           menuItemName + ";" +
           std::to_string(menuItemType) + ";" +
           std::to_string(availability) + ";" +
           std::to_string(price);
  }

  void deserialize(const std::string& data) override {
    std::istringstream iss(data);
    std::string token;

    std::getline(iss, token, ';');
    menuItemId = std::stoi(token);

    std::getline(iss, token, ';');
    menuItemName = token;

    std::getline(iss, token, ';');
    menuItemType = static_cast<MenuItemType>(std::stoi(token));

    std::getline(iss, token, ';');
    availability = std::stoi(token);

    std::getline(iss, token, ';');
    price = std::stoi(token);
  }
};
