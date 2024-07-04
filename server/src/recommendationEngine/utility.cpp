#include "../../inc/recommendationEngine/utility.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::string Utility::toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<std::string> Utility::splitWords(const std::string &str) {
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

std::unordered_set<std::string> Utility::readWordsFromCSV(const std::string &filename) {
    std::unordered_set<std::string> words;
    std::ifstream file(filename);
    std::cout << "Reading file: " << filename << std::endl;
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return words;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ',')) {
            word = toLower(word);
            std::cout << "Word read: " << word << std::endl;
            words.insert(word);
        }
    }

    std::cout << "Total words loaded from " << filename << ": " << words.size() << std::endl;
    return words;
}

