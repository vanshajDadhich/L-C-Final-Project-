#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>

class Utility {
public:
    std::string toLower(const std::string &str);
    std::vector<std::string> splitWords(const std::string &str);
    std::unordered_set<std::string> readWordsFromCSV(const std::string &filename);
};

#endif