#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "IUserController.h"
#include "../service/feedbackService.h"
#include "../service/recommandationSelectionService.h"

class EmployeeController : public IUserController {
    private :
    FeedbackService* feedbackService;
    RecommendationSelectionService* recommandationSelectionService;

public:
    EmployeeController(FeedbackService* feedbackService, RecommendationSelectionService* recommandationSelectionService);
    std::string handleRequest(Operation operation, std::string request) override;

};

#endif