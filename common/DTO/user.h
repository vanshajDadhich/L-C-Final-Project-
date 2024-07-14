#ifndef USER_H
#define USER_H

#include "serializable.h"

enum Role : int { Admin = 1, Employee = 2, Chef = 3 };

struct User : public Serializable {
    int userId = 0;
    std::string name;
    std::string password;
    Role role;

    User(int userId = 0, std::string name = "", int role = 0, std::string password = "")
        : userId(userId), name(name), password(password), role(static_cast<Role>(role)) {}

    std::string serialize() const override {
        return std::to_string(userId) + ";" + name + ";" + std::to_string(static_cast<int>(role)) + ";" + password;
    }

    void deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string token;
        std::getline(iss, token, ';');
        userId = std::stoi(token);
        std::getline(iss, token, ';');
        name = token;
        std::getline(iss, token, ';');
        role = static_cast<Role>(std::stoi(token));
        std::getline(iss, token, ';');
        password = token;
    }
};

#endif