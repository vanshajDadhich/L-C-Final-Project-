#include "../../inc/service/userService.h"
#include<iostream>

UserService::UserService(std::unique_ptr<IUserDAO> userDAO)
    : userDAO(std::move(userDAO)) {}

bool UserService::addUser(const User& user) {
    return userDAO->addUser(user);
}

User UserService::getUserById(int userId) {
    return userDAO->getUserByID(userId);
}

std::vector<User> UserService::getAllUsers() {
    return userDAO->getAllUsers();
}