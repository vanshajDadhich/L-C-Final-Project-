#pragma once

#include <string>
#include <sstream>
#include "serializable.h"
#include<iostream>

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
   login = 11,
   GetRecommandationFromEngine = 12,
   GetTodaysMenu = 13,
   GetChefRollOutMenuForTomorrow = 14

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
};
