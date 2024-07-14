#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "../DTO/menuItem.h"

namespace Utility {
    std::string getMenuItemType(MenuItemType menuItemType);
    std::string getVegetarianPreference(VegetarianPreference vegetarianPreference);
    std::string getSpiceLevelOption(SpiceLevelOption spiceLevelOption);
    std::string getCuisinePreference(CuisinePreference cuisinePreference);
    std::string getSweetToothPreference(SweetToothPreference sweetToothPreference);
    int getValidatedChoice(int min, int max);
    std::string toLower(const std::string &str);
    std::vector<std::string> splitWords(const std::string &str);
    std::unordered_set<std::string> readWordsFromCSV(const std::string &filename);
}

#endif // UTILITY_H
