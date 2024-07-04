#ifndef IUSERCONTROLLER_H
#define IUSERCONTROLLER_H

#include <vector>
#include <string>
#include "../DTO/serializationUtility.h"

class IUserController
{
public:
    virtual std::string handleRequest(Operation operation, const std::string& request) = 0;
};

#endif