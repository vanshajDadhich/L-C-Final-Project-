#include "../inc/vectorSerializer.h"
#include <sstream>
#include <ostream>

std::string VectorSerializer::serialize(std::vector<std::string> vec) {
    std::string serializedString;
    for (const auto& str : vec) {
        serializedString += str + '$';
    }
    if (!serializedString.empty()) {
        serializedString.pop_back();
    }
    return serializedString;
}

std::vector<std::string> VectorSerializer::deserialize(const std::string& serialized) {
    std::vector<std::string> result;
    std::string token;
    std::istringstream tokenStream(serialized);
    while (std::getline(tokenStream, token, '$')) {
        result.push_back(token);
    }
    return result;
}
