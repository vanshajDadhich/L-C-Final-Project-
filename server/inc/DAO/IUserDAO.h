#ifndef IUSERDAO_H
#define IUSERDAO_H

#include "../DTO/user.h"
#include <vector>

class IUserDAO {
public:

    virtual int addUser(const User& user) = 0;

    virtual User getUserByID(const int& userId) = 0;

    virtual std::vector<User> getAllUsers() = 0;
};

#endif // IUSERDAO_H
