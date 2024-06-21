#include "IUserController.h"
#include "../service/feedbackService.h"
#include "../service/recommandationSelectionService.h"

class EmployeeController : public IUserController {
    private :
    FeedbackService* feedbackService;
    RecommendationSelectionService* recommandationSelectionService;

public:
    EmployeeController(FeedbackService* feedbackService, RecommendationSelectionService* recommandationSelectionService);
    std::vector<std::string> handleRequest(std::vector<std::string> request) override;

};