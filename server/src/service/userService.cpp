#include "../../inc/service/userService.h"
#include<iostream>

UserService::UserService(IUserDAO* userDAO)
    : userDAO(userDAO) {}

bool UserService::addUser(const User& user) {
    return userDAO->addUser(user);
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
    if(user.userId == userId && user.password == password) {
        return user.role;
    }
    return -1;
}