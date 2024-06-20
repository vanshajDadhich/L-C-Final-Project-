#include"../../inc/serverProcess/requestProcessor.h"
#include<iostream>
#include<vector>
#include"../../inc/DAO/userDAO.h"


RequestProcessor::RequestProcessor() {
    DatabaseConnection::initDbConnection("tcp://127.0.0.1:3306", "root", "Vanshaj@123", "databaseRecommendationEngine");
    UserDAO* userDAO = new UserDAO();
    UserService* userService = new UserService(userDAO);
    this->authenticationController = new AuthenticationController(userService);
}

std::vector<std::string> RequestProcessor::processRequest(std::vector<std::string> request){
    std::vector<std::string> response;
    bool userAuthenticated = false;
    std::cout<<"processing request: 17\n";
    switch (std::stoi(request[0])) {
        case Operation::login:
            std::cout<<"processing request: 20 login \n";
            userAuthenticated = authenticationController->authenticateUser(std::stoi(request[1]), request[2]);
            std::cout<<"processing request: userAuthenticated : "<<userAuthenticated<<"\n";
            if(userAuthenticated){
                response = {"UserAuthenticated"};
            }
            break;
        default:
            response = {"Invalid Operation"};
            break;
    }
    
    return response;
}