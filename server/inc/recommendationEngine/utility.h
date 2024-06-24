// #pragma once
// #include <iostream>
// #include <fstream>
// #include <algorithm>
// #include <unordered_set>

// class Utility
// {
// public:
//    static std::string toLower(const std::string &str);

//    static std::vector<std::string> splitWords(const std::string &str);

//    static std::unordered_set<std::string> readWordsFromFile(const std::string &filename);
// };


#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>

class Utility {
public:
    static std::string toLower(const std::string &str);
    static std::vector<std::string> splitWords(const std::string &str);
    static std::unordered_set<std::string> readWordsFromFile(const std::string &filename);
};
