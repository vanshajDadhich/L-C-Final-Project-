#include "../../inc/controller/employeeController.h"

EmployeeController::EmployeeController(FeedbackService* feedbackService, RecommendationSelectionService* recommandationSelectionService) : feedbackService(feedbackService), recommandationSelectionService(recommandationSelectionService)  {}


std::string EmployeeController::handleRequest(Operation operation,std::string request) {
    std::string response;

    switch (operation) {
        case Operation::GetMenuAndProvideFeedback:
           
            break;
        case Operation::SelectItemFromTomorrowMenu:
            
            break;
        default:
            response = "Invalid operation";
            break;
    }
    return response;
}

