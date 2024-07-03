// #pragma once

// #include <string>
// #include <sstream>
// #include "serializable.h"

// enum MenuItemType : int { Breakfast = 1, Lunch = 2, Dinner = 3 };

// struct MenuItem : public Serializable {
//   int menuItemId = 0;
//   std::string menuItemName;
//   MenuItemType menuItemType;
//   bool availability;
//   int price;

//   MenuItem(int menuItemId = 0, std::string menuItemName = "", int menuItemType = 0,
//            bool availability = false, int price = 0)
//       : menuItemId(menuItemId), menuItemName(menuItemName), 
//         menuItemType(static_cast<MenuItemType>(menuItemType)), 
//         availability(availability), price(price) {}


//   std::string serialize() const override {
//     return std::to_string(menuItemId) + ";" +
//            menuItemName + ";" +
//            std::to_string(menuItemType) + ";" +
//            std::to_string(availability) + ";" +
//            std::to_string(price);
//   }

//   void deserialize(const std::string& data) override {
//     std::istringstream iss(data);
//     std::string token;

//     std::getline(iss, token, ';');
//     menuItemId = std::stoi(token);

//     std::getline(iss, token, ';');
//     menuItemName = token;

//     std::getline(iss, token, ';');
//     menuItemType = static_cast<MenuItemType>(std::stoi(token));

//     std::getline(iss, token, ';');
//     availability = std::stoi(token);

//     std::getline(iss, token, ';');
//     price = std::stoi(token);
//   }
// };


#pragma once

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
  VegetarianPreference vegetarianPreference = VegetarianPreference::NonVegetarian; // Default
  SpiceLevelOption spiceLevelOption = SpiceLevelOption::Medium; // Default
  FoodPreference foodPreference = FoodPreference::NorthIndian; // Default
  SweetToothPreference sweetToothPreference = SweetToothPreference::No; // Default

  MenuItem(int menuItemId = 0, std::string menuItemName = "", MenuItemType menuItemType = MenuItemType::Breakfast,
           bool availability = false, int price = 0,
           VegetarianPreference vegetarianPreference = VegetarianPreference::NonVegetarian,
           SpiceLevelOption spiceLevelOption = SpiceLevelOption::Medium,
           FoodPreference foodPreference = FoodPreference::NorthIndian,
           SweetToothPreference sweetToothPreference = SweetToothPreference::No)
      : menuItemId(menuItemId), menuItemName(menuItemName), menuItemType(menuItemType),
        availability(availability), price(price),
        vegetarianPreference(vegetarianPreference),
        spiceLevelOption(spiceLevelOption),
        foodPreference(foodPreference),
        sweetToothPreference(sweetToothPreference) {}

  std::string serialize() const override {
    return std::to_string(menuItemId) + ";" +
           menuItemName + ";" +
           std::to_string(static_cast<int>(menuItemType)) + ";" +
           std::to_string(availability) + ";" +
           std::to_string(price) + ";" +
           std::to_string(static_cast<int>(vegetarianPreference)) + ";" +
           std::to_string(static_cast<int>(spiceLevelOption)) + ";" +
           std::to_string(static_cast<int>(foodPreference)) + ";" +
           std::to_string(static_cast<int>(sweetToothPreference));
  }

  void deserialize(const std::string& data) override {
    std::istringstream iss(data);
    std::string token;

    // Read menuItemId
    if (std::getline(iss, token, ';'))
      menuItemId = std::stoi(token);

    // Read menuItemName
    if (std::getline(iss, token, ';'))
      menuItemName = token;

    // Read menuItemType
    if (std::getline(iss, token, ';'))
      menuItemType = static_cast<MenuItemType>(std::stoi(token));

    // Read availability
    if (std::getline(iss, token, ';'))
      availability = std::stoi(token);

    // Read price
    if (std::getline(iss, token, ';'))
      price = std::stoi(token);

    // Read vegetarianPreference
    if (std::getline(iss, token, ';'))
      vegetarianPreference = static_cast<VegetarianPreference>(std::stoi(token));

    // Read spiceLevelOption
    if (std::getline(iss, token, ';'))
      spiceLevelOption = static_cast<SpiceLevelOption>(std::stoi(token));

    // Read foodPreference
    if (std::getline(iss, token, ';'))
      foodPreference = static_cast<FoodPreference>(std::stoi(token));

    // Read sweetToothPreference
    if (std::getline(iss, token, ';'))
      sweetToothPreference = static_cast<SweetToothPreference>(std::stoi(token));
  }
};
