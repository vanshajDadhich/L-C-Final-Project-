#ifndef USERSERVICE_H
#define USERSERVICE_H

#include"../DAO/IUserDAO.h"

class UserService
{
public:
    UserService(IUserDAO* userDAO);
    bool addUser(std::vector<std::string> userData);
    bool deleteUserByID(int userId);
    User getUserById(int userId);

    std::vector<User> getAllUsers();
    int authenticateUser(const int& userId, const std::string& password);

    ~UserService() = default;
private:    
    IUserDAO* userDAO;
    int userIdcounter = 10;
};

#endif // USERSERVICE_H
