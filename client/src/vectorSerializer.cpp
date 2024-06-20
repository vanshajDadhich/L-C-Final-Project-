#include "../inc/vectorSerializer.h"
#include <sstream>
#include <ostream>
 
std::string VectorSerializer::serialize(std::vector<std::string> data)
{
    std::ostringstream serializedString;
    for (size_t i = 0; i < data.size(); ++i) {
        serializedString << data[i];
        if (i != data.size() - 1) {
            serializedString << ",";
        }
    }
    return serializedString.str();
}

std::vector<std::string> VectorSerializer::deserialize(const std::string& data)
{
   std::vector<std::string> splittedString;
    std::istringstream iss(data);
    std::string sepratedString;
   
    while (std::getline(iss, sepratedString, ',')) {
        splittedString.push_back(sepratedString);
    }
   
    return splittedString;
}