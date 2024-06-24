#include "../../inc/controller/employeeController.h"

EmployeeController::EmployeeController(FeedbackService* feedbackService, NextDayMenuVotingService* nextDayMenuVotingService, MenuItemService* menuItemService) 
        : feedbackService(feedbackService), nextDayMenuVotingService(nextDayMenuVotingService), menuItemService(menuItemService) {}


std::string EmployeeController::handleRequest(Operation operation,std::string request) {
    std::cout<<"Handle request in Chef Controller\n";
    std::string response;
    if (operation == Operation::ViewNotification) {
        
    }
    else if(operation == Operation::ProvideFeedback){
        Feedback feedback = SerializationUtility::deserialize<Feedback>(request);
        bool operationDone = feedbackService->addFeedback(feedback);
        std::cout<<"FeedBack Added : "<<operationDone<<std::endl;
    }
    else if(operation == Operation::GetTodaysMenu){

    }
    else if(operation == Operation::VoteItemFromTomorrowMenu){
        int menuItemId = std::stoi(request);
        bool operationDone = nextDayMenuVotingService->increaseVoteCountForMenuItemId(menuItemId);
        std::cout<<"Increased Count for menuItemID provided"<<std::endl;
    }
    else if(operation == Operation::GetChefRollOutMenuForTomorrow)
    {  
        std::vector<NextDayMenuRollOut> chefRolloutMenuForNextDay = getNextDayMenuItemsToRollOut();
        std::vector<std::string> recommendedMenuItemSerializedData;
        for (auto menu : chefRolloutMenuForNextDay) {
            recommendedMenuItemSerializedData.push_back(SerializationUtility::serialize(menu));
        }
        response = VectorSerializer::serialize(recommendedMenuItemSerializedData);

    }
    else {
        response = "Invalid operation";
    }
    return response;
}

std::vector<NextDayMenuRollOut> EmployeeController::getNextDayMenuItemsToRollOut() {
    std::vector<NextDayMenuVoting> nextDayMenuVotingList = nextDayMenuVotingService->getAllNextDayMenuRollOutItem();
    std::vector<NextDayMenuRollOut> nextDayMenuRollOutItems;

    for (const auto& nextDayMenuItemId : nextDayMenuVotingList) {
        // Retrieve the menu item details using menuService
        MenuItem menuItem = menuItemService->getMenuItemById(nextDayMenuItemId.menuItemId);

        // Create NextDayMenuRollOut object
        NextDayMenuRollOut rollOutItem(
            menuItem.menuItemId,
            menuItem.menuItemName,
            menuItem.menuItemType,
            menuItem.price,
            nextDayMenuItemId.voteCount,        // Assuming this should be set as selectionCount
            nextDayMenuItemId.rating,
            nextDayMenuItemId.sentimentScore
        );

        // Add to the result vector
        nextDayMenuRollOutItems.push_back(rollOutItem);
    }

    return nextDayMenuRollOutItems;
}

