#ifndef IUSERCONTROLLER_H
#define IUSERCONTROLLER_H

#include <vector>
#include <string>
#include "../DTO/SerializationUtility.h"



class IUserController
{
public:
    virtual std::string handleRequest(Operation operation, std::string request) = 0;
};

#endif // IUSERCONTROLLER_H