#include "../../inc/service/userService.h"
#include<iostream>

UserService::UserService(IUserDAO* userDAO)
    : userDAO(userDAO) {}

bool UserService::addUser(std::vector<std::string> userData) {
    std::cout<<"User Service 10\n";
    if(userData[3] == "Admin") {
        userData[3] = "1";
    } else if(userData[3] == "Chef") {
        userData[3] = "2";
    } else if(userData[3] == "Employee") {
        userData[3] = "3";
    }
    userIdcounter++;
    std::cout<<"User Service 20\n"<<userData[1]<<" "<<userData[2]<<" "<<userData[3]<<" "<<userIdcounter<<"\n";
    User user(userIdcounter, userData[1],std::stoi(userData[3]), userData[2]);
    return userDAO->addUser(user);
}

bool UserService::deleteUserByID(int userId) {
    return userDAO->deleteUser(userId);
}

User UserService::getUserById(int userId) {
    return userDAO->getUserByID(userId);
}

std::vector<User> UserService::getAllUsers() {
    return userDAO->getAllUsers();
}

int UserService::authenticateUser(const int& userId, const std::string& password) {
    std::cout<<"Authenticating User : userService 27\n";
    User user = userDAO->getUserByID(userId);
    std::cout<<"user "<<user.userId<<" "<<user.name<<" "<<user.password<<" "<<user.role<<" "<<"\n";
    if(user.userId == userId || user.password == password) {
        return user.role;
    }
    return -1;
}