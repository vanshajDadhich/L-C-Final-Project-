#ifndef CHEFCONTROLLER_H
#define CHEFCONTROLLER_H

#include "IUserController.h"

class ChefController : public IUserController {
    
public:
    ChefController();
    std::string handleRequest(Operation operation, std::string request) override;
};

#endif