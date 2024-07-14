#ifndef NEXTDAYMENUROLLOUT_H
#define NEXTDAYMENUROLLOUT_H

#include "serializable.h"
#include "menuItem.h"
#include <sstream>
#include <string>

struct NextDayMenuRollOut : public Serializable {
    int menuItemId;
    std::string menuItemName;
    MenuItemType menuItemType;
    int price;
    int selectionCount;
    double averageRating;
    std::string sentiments;

    NextDayMenuRollOut(int menuItemId = 0, const std::string& menuItemName = "", MenuItemType menuItemType = MenuItemType::Breakfast,
                       int price = 0, int selectionCount = 0, double averageRating = 0, std::string sentiments = "")
        : menuItemId(menuItemId), menuItemName(menuItemName), menuItemType(menuItemType), price(price),
          selectionCount(selectionCount), averageRating(averageRating), sentiments(sentiments) {}

    std::string serialize() const override {
        return std::to_string(menuItemId) + ";" +
               menuItemName + ";" +
               std::to_string(static_cast<int>(menuItemType)) + ";" +
               std::to_string(price) + ";" +
               std::to_string(selectionCount) + ";" +
               std::to_string(averageRating) + ";" +
               sentiments;
    }

    void deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string token;

        std::getline(iss, token, ';');
        menuItemId = std::stoi(token);

        std::getline(iss, menuItemName, ';');

        std::getline(iss, token, ';');
        menuItemType = static_cast<MenuItemType>(std::stoi(token));

        std::getline(iss, token, ';');
        price = std::stoi(token);

        std::getline(iss, token, ';');
        selectionCount = std::stoi(token);

        std::getline(iss, token, ';');
        averageRating = std::stod(token);

        std::getline(iss, sentiments, ';');
    }
};

#endif