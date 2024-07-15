#include "../../inc/communication/requestProcessor.h"
#include "../../inc/DAO/userDAO.h"
#include "../../inc/DAO/menuItemDAO.h"
#include "../../inc/DAO/feedbackDAO.h"
#include "../../inc/DAO/nextDayMenuVotingDAO.h"
#include "../../inc/controller/adminController.h"
#include "../../inc/controller/chefController.h"
#include "../../inc/controller/employeeController.h"
#include "../../inc/DAO/todayMenuDAO.h"
#include "../../inc/DAO/notificationDAO.h"
#include "../../inc/DAO/discardMenuItemDetailedFeedbackDAO.h"
#include "../../inc/DAO/userProfileDAO.h"

RequestProcessor::RequestProcessor() {
    DatabaseConnection::initDbConnection("tcp://127.0.0.1:3306", "root", "Vanshaj@123", "databaseRecommendationEngine");
    auto userService = std::make_unique<UserService>(std::make_unique<UserDAO>());
    authenticationController = std::make_unique<AuthenticationController>(std::move(userService));
}

std::unique_ptr<IUserController> RequestProcessor::initializeAdminController() {
    auto menuItemService = std::make_unique<MenuItemService>(std::make_unique<MenuItemDAO>());
    auto userService = std::make_unique<UserService>(std::make_unique<UserDAO>());
    auto notificationService = std::make_unique<NotificationService>(std::make_unique<NotificationDAO>());
    return std::make_unique<AdminController>(std::move(menuItemService), std::move(userService), std::move(notificationService));
}

std::unique_ptr<IUserController> RequestProcessor::initializeEmployeeController() {
    auto feedbackService = std::make_unique<FeedbackService>(std::make_unique<FeedbackDAO>());
    auto nextDayMenuVotingService = std::make_unique<NextDayMenuVotingService>(std::make_unique<NextDayMenuVotingDAO>());
    auto menuItemService = std::make_unique<MenuItemService>(std::make_unique<MenuItemDAO>());
    auto todayMenuService = std::make_unique<TodayMenuService>(std::make_unique<TodayMenuDAO>());
    auto notificationService = std::make_unique<NotificationService>(std::make_unique<NotificationDAO>());
    auto discardMenuItemDetailedFeedbackService = std::make_unique<DiscardMenuItemDetailedFeedbackService>(std::make_unique<DiscardMenuItemDetailedFeedbackDAO>());
    auto userProfileService = std::make_unique<UserProfileService>(std::make_unique<UserProfileDAO>());
    auto recommendationEngine = std::make_unique<RecommendationEngine>();
    return std::make_unique<EmployeeController>(
        std::move(menuItemService),
        std::move(nextDayMenuVotingService),
        std::move(feedbackService),
        std::move(recommendationEngine),
        std::move(todayMenuService),
        std::move(notificationService),
        std::move(userProfileService),
        std::move(discardMenuItemDetailedFeedbackService)
    );
}

std::unique_ptr<IUserController> RequestProcessor::initializeChefController() {
    auto menuItemService = std::make_unique<MenuItemService>(std::make_unique<MenuItemDAO>());
    auto nextDayMenuVotingService = std::make_unique<NextDayMenuVotingService>(std::make_unique<NextDayMenuVotingDAO>());
    auto feedbackService = std::make_unique<FeedbackService>(std::make_unique<FeedbackDAO>());
    auto recommendationEngine = std::make_unique<RecommendationEngine>();
    auto todayMenuService = std::make_unique<TodayMenuService>(std::make_unique<TodayMenuDAO>());
    auto notificationService = std::make_unique<NotificationService>(std::make_unique<NotificationDAO>());
    return std::make_unique<ChefController>(
        std::move(menuItemService),
        std::move(nextDayMenuVotingService),
        std::move(feedbackService),
        std::move(recommendationEngine),
        std::move(todayMenuService),
        std::move(notificationService)
    );
}

std::string RequestProcessor::processRequest(const std::string& request) {
    std::pair<Operation, std::string> requestData;
    std::string response;

    try {
        requestData = SerializationUtility::deserializeOperation(request);

        if (requestData.first == Operation::LoginUser) {
            response = handleLoginRequest(requestData.second);
        } else {
            response = handleUserRequest(requestData.first, requestData.second);
        }
    } catch (const QueryException& e) {
        std::cerr << "QueryException: " << e.what() << std::endl;
        response = "Error: Query failed.";
    } catch (const ConnectException& e) {
        std::cerr << "ConnectException: " << e.what() << std::endl;
        response = "Error: Connection to database failed.";
    } catch (const InitializationException& e) {
        std::cerr << "InitializationException: " << e.what() << std::endl;
        response = "Error: Initialization failed.";
    } catch (const DatabaseException& e) {
        std::cerr << "DatabaseException: " << e.what() << std::endl;
        response = "Error: Database operation failed.";
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        response = "Error: An unexpected error occurred.";
    }

    return response;
}

std::string RequestProcessor::handleLoginRequest(const std::string& requestData) {
    int userAuthenticated = authenticationController->authenticateUser(requestData);
    std::string response = std::to_string(userAuthenticated);

    if (userAuthenticated == 1) {
        std::cout << "Admin LoggedIn" << std::endl;
        userController = initializeAdminController();
    } else if (userAuthenticated == 2) {
        std::cout << "Employee LoggedIn" << std::endl;
        userController = initializeEmployeeController();
    } else if (userAuthenticated == 3) {
        std::cout << "Chef LoggedIn" << std::endl;
        userController = initializeChefController();
    } else {
        std::cout << "Invalid Username Password" << std::endl;
    }
    return response;
}

std::string RequestProcessor::handleUserRequest(Operation operation, const std::string& requestData) {
    std::string response;
    std::cout << "[Request Processor] Handle Request" << std::endl;
    if (userController) {
        response =  userController->handleRequest(operation, requestData);
    } else {
        response =  "User not authenticated";
    }  
    return response;
}
