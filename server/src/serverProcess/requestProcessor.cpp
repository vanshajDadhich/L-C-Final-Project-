#include"../../inc/serverProcess/requestProcessor.h"
#include<iostream>
#include<vector>
#include"../../inc/DAO/userDAO.h"
#include"../../inc/DAO/menuItemDAO.h"
#include"../../inc/DAO/feedbackDAO.h"
#include"../../inc/DAO/RecommendationSelectionDAO.h"
#include"../../inc/controller/adminController.h"
#include"../../inc/controller/chefController.h"
#include"../../inc/controller/employeeController.h"

RequestProcessor::RequestProcessor() {
    DatabaseConnection::initDbConnection("tcp://127.0.0.1:3306", "root", "Vanshaj@123", "databaseRecommendationEngine");
    UserDAO* userDAO = new UserDAO();
    this->userService = new UserService(userDAO);
    this->authenticationController = new AuthenticationController(this->userService);
    MenuItemDAO* menuItemDAO = new MenuItemDAO();
    this->menuItemService = new MenuItemService(menuItemDAO);
    FeedbackDAO* feedbackDAO = new FeedbackDAO();
    this->feedbackService = new FeedbackService(feedbackDAO);
    RecommendationSelectionDAO* recommendationSelectionDAO = new RecommendationSelectionDAO();
    this->recommendationSelectionService = new RecommendationSelectionService(recommendationSelectionDAO);
}

std::string RequestProcessor::processRequest(std::string request){
    std::pair<Operation, std::string> requestData = SerializationUtility::deserializeOperation(request);
    std::string response;
    int userAuthenticated;
    std::cout<<"processing request: 17\n";
    switch (requestData.first) {
        case Operation::login:
            userAuthenticated = authenticationController->authenticateUser(requestData.second);
            if(userAuthenticated == 1){
                userController = new AdminController(menuItemService, userService);
                response = "1";
            }else if(userAuthenticated == 2){
                response = "2";
                userController = new ChefController();
            }else if(userAuthenticated == 3){
                response = "3";
                userController = new EmployeeController(feedbackService, recommendationSelectionService);
            }else{
                response = "-1";
            }
            break;
        case Operation::AddUser: 
        case Operation::AddMenuItem:
        case Operation::DeleteMenuItem:
        case Operation::UpdateMenuItem:
        case Operation::ViewMenu:
        case Operation::RollOutMenuForNextDay:
        case Operation::GenerateReport:
        case Operation::PublishMenuForToday:
        case Operation::ViewNotification:
        case Operation::GetMenuAndProvideFeedback:
        case Operation::SelectItemFromTomorrowMenu:
            std::cout<<"Handle Request called\n";
            response = userController->handleRequest(requestData.first, requestData.second);
            break;
        default:
            response = {"Invalid Operation"};
            break;
    }
    
    return response;
}