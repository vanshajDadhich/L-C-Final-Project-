#include "utility.h"
#include <limits>
#include <iostream>

namespace Utility {
    std::string getMenuItemType(MenuItemType menuItemType) {
        return menuItemType == MenuItemType::Breakfast ? "Breakfast" :
               menuItemType == MenuItemType::Lunch ? "Lunch" :
               menuItemType == MenuItemType::Dinner ? "Dinner" : "Unknown";
    }

    std::string getVegetarianPreference(VegetarianPreference vegetarianPreference) {
        return vegetarianPreference == VegetarianPreference::Vegetarian ? "Vegetarian" :
               vegetarianPreference == VegetarianPreference::NonVegetarian ? "Non Vegetarian" :
               vegetarianPreference == VegetarianPreference::Eggetarian ? "Eggetarian" : "Unknown";
    }

    std::string getSpiceLevelOption(SpiceLevelOption spiceLevelOption) {
        return spiceLevelOption == SpiceLevelOption::High ? "High" :
               spiceLevelOption == SpiceLevelOption::Medium ? "Medium" :
               spiceLevelOption == SpiceLevelOption::Low ? "Low" : "Unknown";
    }

    std::string getCuisinePreference(CuisinePreference cuisinePreference) {
        return cuisinePreference == CuisinePreference::NorthIndian ? "North Indian" :
               cuisinePreference == CuisinePreference::SouthIndian ? "South Indian" :
               cuisinePreference == CuisinePreference::Other ? "Other" : "Unknown";
    }

    std::string getSweetToothPreference(SweetToothPreference sweetToothPreference) {
        return sweetToothPreference == SweetToothPreference::Yes ? "Yes" : "No";
    }

    int getValidatedChoice(int min, int max) {
        int choice;
        while (true) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter your choice (" << min << " to " << max << "): ";
            if (std::cin >> choice && choice >= min && choice <= max) {
                return choice;
            }
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": " << std::endl;
        }
    }

    std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<std::string> splitWords(const std::string &str) {
    std::vector<std::string> words;
    std::string word;
    for (char c : str) {
        if (std::isspace(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

}
