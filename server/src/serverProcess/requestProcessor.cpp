#include"../../inc/serverProcess/requestProcessor.h"
#include<iostream>
#include<vector>
#include"../../inc/DAO/userDAO.h"
#include"../../inc/DAO/menuItemDAO.h"
#include"../../inc/DAO/feedbackDAO.h"
#include"../../inc/DAO/nextDayMenuVotingDAO.h"
#include"../../inc/controller/adminController.h"
#include"../../inc/controller/chefController.h"
#include"../../inc/controller/employeeController.h"
#include "../../inc/DAO/todayMenuDAO.h"
#include "../../inc/DAO/notificationDAO.h"

RequestProcessor::RequestProcessor() {
    DatabaseConnection::initDbConnection("tcp://127.0.0.1:3306", "root", "Vanshaj@123", "databaseRecommendationEngine");
    UserDAO* userDAO = new UserDAO();
    this->userService = new UserService(userDAO);
    this->authenticationController = new AuthenticationController(this->userService);
    MenuItemDAO* menuItemDAO = new MenuItemDAO();
    this->menuItemService = new MenuItemService(menuItemDAO);
    FeedbackDAO* feedbackDAO = new FeedbackDAO();
    this->feedbackService = new FeedbackService(feedbackDAO);
    NextDayMenuVotingDAO* nextDayMenuVotingDAO = new NextDayMenuVotingDAO();
    this->nextDayMenuVotingService = new NextDayMenuVotingService(nextDayMenuVotingDAO);
    this->recommendationEngine = new RecommendationEngine();
    std::shared_ptr<ITodayMenuDAO> todayMenuDAO = std::make_shared<TodayMenuDAO>();
    this->todayMenuService = new TodayMenuService(todayMenuDAO);
    std::shared_ptr<NotificationDAO> notificationDAO = std::make_shared<NotificationDAO>();
    this->notificationService = new NotificationService(notificationDAO);
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
                std::cout<<"Admin LoggedIn"<<std::endl;
                userController = new AdminController(menuItemService, userService, notificationService);
            }else if(userAuthenticated == 2){
                std::cout<<"Chef LoggedIn"<<std::endl;
                userController = new ChefController(menuItemService, nextDayMenuVotingService, feedbackService, recommendationEngine, todayMenuService, notificationService);
            }else if(userAuthenticated == 3){
                std::cout<<"Employee LoggedIn"<<std::endl;
                userController = new EmployeeController(feedbackService, nextDayMenuVotingService, menuItemService, todayMenuService, notificationService);
            }else{
                std::cout<<"Invalid Username Password"<<std::endl;
            }
            response = std::to_string(userAuthenticated);
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
        case Operation::ProvideFeedback:
        case Operation::VoteItemFromTomorrowMenu:
        case Operation::GetRecommandationFromEngine:
        case Operation::GetTodaysMenu:
        case Operation::GetChefRollOutMenuForTomorrow:
            std::cout<<"Handle Request called\n";
            response = userController->handleRequest(requestData.first, requestData.second);
            break;
        default:
            response = {"Invalid Operation"};
            break;
    }
    
    
    return response;
}