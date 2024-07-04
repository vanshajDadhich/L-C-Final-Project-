#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "serializable.h"
#include <sstream>

enum VegetarianPreference : int {
    Vegetarian = 1,
    NonVegetarian = 2,
    Eggetarian = 3
};

enum SpiceLevelOption : int {
    High = 1,
    Medium = 2,
    Low = 3
};

enum FoodPreference : int {
    NorthIndian = 1,
    SouthIndian = 2,
    Other = 3
};

enum SweetToothPreference : int {
    Yes = 1,
    No = 0
};

struct UserProfile : public Serializable {
    int userId = 0;
    VegetarianPreference vegetarianPreference ;
    SpiceLevelOption spiceLevelOption;
    FoodPreference foodPreference;
    SweetToothPreference sweetToothPreference;

    UserProfile(int userId = 0, VegetarianPreference vegetarianPreference = VegetarianPreference::Vegetarian, SpiceLevelOption spiceLevelOption  = SpiceLevelOption::High, 
                FoodPreference foodPreference = FoodPreference::NorthIndian, SweetToothPreference sweetToothPreference = SweetToothPreference::Yes)
        : userId(userId), vegetarianPreference(vegetarianPreference), spiceLevelOption(spiceLevelOption), 
          foodPreference(foodPreference), sweetToothPreference(sweetToothPreference) {}

    std::string serialize() const override {
        return std::to_string(userId) + ";" + std::to_string(static_cast<int>(vegetarianPreference)) + ";" + 
               std::to_string(static_cast<int>(spiceLevelOption)) + ";" + std::to_string(static_cast<int>(foodPreference)) + ";" + 
               std::to_string(static_cast<int>(sweetToothPreference));
    }

    void deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string token;
        std::getline(iss, token, ';');
        userId = std::stoi(token);
        std::getline(iss, token, ';');
        vegetarianPreference = static_cast<VegetarianPreference>(std::stoi(token));
        std::getline(iss, token, ';');
        spiceLevelOption = static_cast<SpiceLevelOption>(std::stoi(token));
        std::getline(iss, token, ';');
        foodPreference = static_cast<FoodPreference>(std::stoi(token));
        std::getline(iss, token, ';');
        sweetToothPreference = static_cast<SweetToothPreference>(std::stoi(token));
    }
};

#endif
