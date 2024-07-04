#ifndef SERIALIZATIONUTILITY_H
#define SERIALIZATIONUTILITY_H

#include <string>
#include <sstream>
#include "serializable.h"
#include<iostream>
#include<vector>

enum Operation : int {
   AddUser = 0,
   AddMenuItem = 1,
   DeleteMenuItem = 2,
   UpdateMenuItem = 3,
   ViewMenu = 4,
   RollOutMenuForNextDay = 5,
   GenerateReport = 6,
   PublishMenuForToday = 7,
   ViewNotification = 8,
   ProvideFeedback = 9,
   VoteItemFromTomorrowMenu = 10,
   LoginUser = 11,
   GetRecommandationFromEngine = 12,
   GetTodaysMenu = 13,
   GetChefRollOutMenuForTomorrow = 14,
   GetDiscardMenuList = 15,
   RemoveMenuItemFromList = 16,
   ProvideDiscardMenuItemDetailedFeedback = 17,
   GetMenuItemIdForDetailFeedbackFromChef = 18
};

class SerializationUtility {
public:
    template <typename T>
    static std::string serialize(const T& obj) {
        return obj.serialize();
    }

    template <typename T>
    static T deserialize(const std::string& data) {
        T obj;
        obj.deserialize(data);
        return obj;
    }

    std::string static serializeOperation(Operation op, const std::string& data) {
        return std::to_string(static_cast<int>(op)) + ';' + data;
    }

    std::pair<Operation, std::string> static deserializeOperation(const std::string& serializedData) {
        std::pair<Operation, std::string> result;
        size_t separatorPos = serializedData.find(';');
        if (separatorPos != std::string::npos) {
            int opInt = std::stoi(serializedData.substr(0, separatorPos));
            result.first = static_cast<Operation>(opInt);
            result.second = serializedData.substr(separatorPos + 1);
        } else {
            std::cerr << "Error: Invalid serialized format" << std::endl;
        }

        return result;
    }

    std::string static serializeStringVector(std::vector<std::string> vec) {
        std::string serializedString;
        for (const auto& str : vec) {
            serializedString += str + '$';
        }
        if (!serializedString.empty()) {
            serializedString.pop_back();
        }
        return serializedString;
    }

    std::vector<std::string> static deserializeStringToVector(const std::string& serialized, char delimeter) {
        std::vector<std::string> result;
        std::string token;
        std::istringstream tokenStream(serialized);
        while (std::getline(tokenStream, token, delimeter)) {
            result.push_back(token);
        }
        return result;
    }
};

#endif