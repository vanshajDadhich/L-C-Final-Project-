#pragma once
#include "serializable.h"
#include <sstream>

enum class VegetarianPreference : int {
    Vegetarian = 0,
    NonVegetarian = 1,
    Eggetarian = 2
};

enum class SpiceLevelOption : int {
    High = 0,
    Medium = 1,
    Low = 2
};

enum class FoodPreference : int {
    NorthIndian = 0,
    SouthIndian = 1,
    Other = 2
};

enum class SweetToothPreference : int {
    Yes = 0,
    No = 1
};

struct UserProfile : public Serializable {
    int userId = 0;
    VegetarianPreference vegetarianPreference = VegetarianPreference::Vegetarian;
    SpiceLevelOption spiceLevelOption = SpiceLevelOption::High;
    FoodPreference foodPreference = FoodPreference::NorthIndian;
    SweetToothPreference sweetToothPreference = SweetToothPreference::Yes;

    UserProfile(int userId, VegetarianPreference vegetarianPreference, SpiceLevelOption spiceLevelOption, 
                FoodPreference foodPreference, SweetToothPreference sweetToothPreference)
        : userId(userId), vegetarianPreference(vegetarianPreference), spiceLevelOption(spiceLevelOption), 
          foodPreference(foodPreference), sweetToothPreference(sweetToothPreference) {}

    UserProfile() {}

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
