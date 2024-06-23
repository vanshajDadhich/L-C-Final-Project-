#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

#include <string>
#include <vector>
#include "../controller/authenticationController.h"
#include "../controller/IUserController.h"
#include "../service/menuItemService.h"
#include "../service/userService.h"
#include "../service/feedbackService.h"
#include "../service/recommandationSelectionService.h"


class RequestProcessor {
    private :
    AuthenticationController* authenticationController;
    IUserController* userController;
    MenuItemService* menuItemService;
    UserService* userService;
    FeedbackService* feedbackService;
    RecommendationSelectionService* recommendationSelectionService;

public:
    RequestProcessor();
    std::string processRequest(std::string request);
};

#endif // REQUESTPROCESSOR_H
