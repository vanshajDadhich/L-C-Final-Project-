#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <sstream>
#include "serializable.h"
#include "userProfile.h"

enum MenuItemType { Breakfast = 1, Lunch = 2, Dinner = 3 };

struct MenuItem : public Serializable {
  int menuItemId = 0;
  std::string menuItemName;
  MenuItemType menuItemType = MenuItemType::Breakfast;
  bool availability = false;
  int price = 0;
  VegetarianPreference vegetarianPreference;
  SpiceLevelOption spiceLevelOption;
  CuisinePreference cuisinePreference;
  SweetToothPreference sweetToothPreference;

  MenuItem(int menuItemId = 0, std::string menuItemName = "", MenuItemType menuItemType = MenuItemType::Breakfast,
           bool availability = false, int price = 0,
           VegetarianPreference vegetarianPreference = VegetarianPreference::NonVegetarian,
           SpiceLevelOption spiceLevelOption = SpiceLevelOption::Medium,
           CuisinePreference cuisinePreference = CuisinePreference::NorthIndian,
           SweetToothPreference sweetToothPreference = SweetToothPreference::No)
      : menuItemId(menuItemId), menuItemName(menuItemName), menuItemType(menuItemType),
        availability(availability), price(price),
        vegetarianPreference(vegetarianPreference),
        spiceLevelOption(spiceLevelOption),
        cuisinePreference(cuisinePreference),
        sweetToothPreference(sweetToothPreference) {}

  std::string serialize() const override {
    return std::to_string(menuItemId) + ";" +
           menuItemName + ";" +
           std::to_string(static_cast<int>(menuItemType)) + ";" +
           std::to_string(availability) + ";" +
           std::to_string(price) + ";" +
           std::to_string(static_cast<int>(vegetarianPreference)) + ";" +
           std::to_string(static_cast<int>(spiceLevelOption)) + ";" +
           std::to_string(static_cast<int>(cuisinePreference)) + ";" +
           std::to_string(static_cast<int>(sweetToothPreference));
  }

  void deserialize(const std::string& data) override {
    std::istringstream iss(data);
    std::string token;

    if (std::getline(iss, token, ';'))
      menuItemId = std::stoi(token);

    if (std::getline(iss, token, ';'))
      menuItemName = token;

    if (std::getline(iss, token, ';'))
      menuItemType = static_cast<MenuItemType>(std::stoi(token));

    if (std::getline(iss, token, ';'))
      availability = std::stoi(token);

    if (std::getline(iss, token, ';'))
      price = std::stoi(token);

    if (std::getline(iss, token, ';'))
      vegetarianPreference = static_cast<VegetarianPreference>(std::stoi(token));

    if (std::getline(iss, token, ';'))
      spiceLevelOption = static_cast<SpiceLevelOption>(std::stoi(token));

    if (std::getline(iss, token, ';'))
      cuisinePreference = static_cast<CuisinePreference>(std::stoi(token));

    if (std::getline(iss, token, ';'))
      sweetToothPreference = static_cast<SweetToothPreference>(std::stoi(token));
  }
};

#endif