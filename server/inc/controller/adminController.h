#include "IUserController.h"
#include "../service/menuItemService.h"
#include "../service/userService.h" 

class AdminController : public IUserController {
    private :
        MenuItemService* menuItemService;
        UserService* userService;

    public:
        AdminController(MenuItemService* menuItemService, UserService* userService);
        std::vector<std::string> handleRequest( std::vector<std::string> request) override;
};