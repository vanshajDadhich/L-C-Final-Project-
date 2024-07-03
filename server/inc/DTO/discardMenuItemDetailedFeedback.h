#pragma once
#include "serializable.h"
#include <string>
#include <sstream>

struct DiscardMenuItemDetailedFeedback : public Serializable {
    int id = 0;
    unsigned long long userId = 0;
    unsigned long long menuItemId = 0;
    std::string whatYouLiked;
    std::string howWouldItTaste;
    std::string shareRecipe;

    DiscardMenuItemDetailedFeedback(int id, unsigned long long userId, unsigned long long menuItemId, 
                                    std::string whatYouLiked, std::string howWouldItTaste, std::string shareRecipe)
        : id(id), userId(userId), menuItemId(menuItemId), whatYouLiked(whatYouLiked), 
          howWouldItTaste(howWouldItTaste), shareRecipe(shareRecipe) {}

    DiscardMenuItemDetailedFeedback() {}

    std::string serialize() const override {
        return std::to_string(id) + ";" + std::to_string(userId) + ";" + std::to_string(menuItemId) + ";" + 
               whatYouLiked + ";" + howWouldItTaste + ";" + shareRecipe;
    }

    void deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string token;
        std::getline(iss, token, ';');
        id = std::stoi(token);
        std::getline(iss, token, ';');
        userId = std::stoull(token);
        std::getline(iss, token, ';');
        menuItemId = std::stoull(token);
        std::getline(iss, token, ';');
        whatYouLiked = token;
        std::getline(iss, token, ';');
        howWouldItTaste = token;
        std::getline(iss, token, ';');
        shareRecipe = token;
    }
};
