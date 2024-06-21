#include "IUserController.h"

class ChefController : public IUserController {
    
public:
    ChefController();
    std::vector<std::string> handleRequest(std::vector<std::string> request) override;

};