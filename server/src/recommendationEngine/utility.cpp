 
// #include "../../inc/recommendationEngine/utility.h"
// #include <iostream>
// #include <fstream>
// #include <algorithm>
 
// std::string Utility::toLower(const std::string &str) {
//     std::string lowerStr = str;
//     std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
//     return lowerStr;
// }
 
// std::vector<std::string> Utility::splitWords(const std::string &str) {
//     std::vector<std::string> words;
//     std::string word;
//     for (char c : str) {
//         if (std::isspace(c)) {
//             if (!word.empty()) {
//                 words.push_back(word);
//                 word.clear();
//             }
//         } else {
//             word += c;
//         }
//     }
//     if (!word.empty()) {
//         words.push_back(word);
//     }
//     return words;
// }
 
// std::unordered_set<std::string> Utility::readWordsFromFile(const std::string &filename) {
//     std::unordered_set<std::string> words;
//     std::ifstream file(filename);
//     std::string word;
//     while (file >> word) {
//         words.insert(word);
//     }
//     return words;
// }
 

#include "../../inc/recommendationEngine/utility.h"

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

std::unordered_set<std::string> Utility::readWordsFromFile(const std::string &filename) {
    std::unordered_set<std::string> words;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        words.insert(word);
    }
    return words;
}