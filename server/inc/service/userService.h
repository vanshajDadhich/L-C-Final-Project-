#ifndef USERSERVICE_H
#define USERSERVICE_H

#include"../DAO/IUserDAO.h"
#include<memory>

class UserService
{
public:
    UserService(std::unique_ptr<IUserDAO> userDAO);
    bool addUser(const User& user);
    User getUserById(int userId);

    std::vector<User> getAllUsers();

    ~UserService() = default;
private:    
    std::unique_ptr<IUserDAO> userDAO;
};

#endif 
