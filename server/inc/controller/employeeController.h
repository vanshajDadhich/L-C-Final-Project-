#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "IUserController.h"
#include "../service/feedbackService.h"
#include "../service/nextDayMenuVotingService.h"
#include "../DTO/nextDayMenuRollout.h"
#include "../service/menuItemService.h"
#include "../serverProcess/vectorSerializer.h"

class EmployeeController : public IUserController {
    private :
    FeedbackService* feedbackService;
    NextDayMenuVotingService* nextDayMenuVotingService;
    MenuItemService* menuItemService;

public:
    EmployeeController(FeedbackService* feedbackService, NextDayMenuVotingService* nextDayMenuVotingService, MenuItemService* menuItemService);
    std::string handleRequest(Operation operation, std::string request) override;
    std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut();

};

#endif