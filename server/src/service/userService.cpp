#include "../../inc/service/userService.h"
#include<iostream>

UserService::UserService(IUserDAO* userDAO)
    : userDAO(userDAO) {}

bool UserService::addUser(const User& user) {
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

bool UserService::authenticateUser(const int& userId, const std::string& password) {
    std::cout<<"Authenticating User : userService 27\n";
    User user = userDAO->getUserByID(userId);
    std::cout<<"user "<<user.userId<<" "<<user.name<<" "<<user.password<<" "<<user.role<<" "<<"\n";
    return user.password == password;
}