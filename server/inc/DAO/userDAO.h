#ifndef USERDAO_H
#define USERDAO_H

#include "IUserDAO.h" 
#include <vector> 
#include "databaseConnection.h"

class UserDAO : public IUserDAO {
public:

    UserDAO();

    bool addUser(const User& user) override;

    bool updateUser(const User& user)  override;

    bool deleteUser(const int& userId) override;

    User getUserByID(const int& userId) override;

    std::vector<User> getAllUsers() override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif 