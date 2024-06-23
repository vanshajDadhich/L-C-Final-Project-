#ifndef LOGIN_H
#define LOGIN_H

#include"serializable.h"
#include<sstream>

struct Login : public Serializable {
    int userId;
    std::string password;

    Login(int userId, std::string password)
       : userId(userId), password(password){}

    Login(){}

    std::string serialize() const override {
        return std::to_string(userId)+ ";" + password;
    }

    void deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string token;
        std::getline(iss, token, ';');
        userId = std::stoi(token);
        std::getline(iss, token, ';');
        password = token;
    }
};

#endif