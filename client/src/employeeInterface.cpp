#include "../inc/employeeInterface.h"
#include <iostream>
#include <limits> 
#include<vector>

EmployeeInterface::EmployeeInterface(RequestHandler* requestHandler, int userIdLoggedIn)
    : requestHandler(requestHandler), userIdLoggedIn(userIdLoggedIn) {}

void EmployeeInterface::showMenu(){
    std::cout << "Welcome Employee\n\n";
    bool flag = true;
    while (flag) {
        std::cout << "Select the operation which you like to perform\n"
                     "1. View Notification\n"
                     "2. View Chef Roll Out Menu For Tomorrow\n" 
                     "3. Select Item you want For tomorrow\n"
                     "4. Today's Menu \n"
                     "5. Provide feedback for today's Menu\n"
                     "6. Provide Detailed Feedback for Discarded Menu Item\n"
                     "7. Exit\n"
                     "Enter your choice: " << std::endl;

        int employeeChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!(std::cin >> employeeChoice)) {
            std::cin.clear();  // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 7: " << std::endl;
        }

        switch (employeeChoice) {
            case 1:
                viewNotification();
                break;
            case 2:
                showChefRollOutMenu();
                break;
            case 3:
                voteForTomorrowMenu();
                break;
            case 4:
                viewTodayMenu();
                break;
            case 5:
                provideFeedbackForTodayMenu();
                break;
            case 6:
                getDetailedFeedbackForDiscardedMenuItem();
                break;
            case 7:
                flag = false;
                break;
            default:
                std::cout << "Invalid Choice" << std::endl;
                break;
        }
    }
}

void EmployeeInterface::getDetailedFeedbackForDiscardedMenuItem(){
    Operation operation = Operation::ProvideDiscardMenuItemDetailedFeedback;
    DiscardMenuItemDetailedFeedback discardMenuItemDetailedFeedback;
    discardMenuItemDetailedFeedback.userId = this->userIdLoggedIn;
    std::cout<<"Provide MenuItem Id you want to provide detailed feedback for: \n";
    std::cin>>discardMenuItemDetailedFeedback.menuItemId;
    std::cout<<"What did you like about the menu item? \n";
    std::cin.ignore();
    std::getline(std::cin, discardMenuItemDetailedFeedback.whatYouLiked);
    std::cout<<"How Would you like this food Item to taste? \n";
    std::cin.ignore();
    std::getline(std::cin, discardMenuItemDetailedFeedback.howWouldItTaste);
    std::cout<<" Share your moms recipe. \n";
    std::cin.ignore();
    std::getline(std::cin, discardMenuItemDetailedFeedback.shareRecipe);
    
    std::string serializedData = SerializationUtility::serialize(discardMenuItemDetailedFeedback);
    std::string serializedDataForRequest = SerializationUtility::serializeOperation(operation, serializedData);
    requestHandler->sendRequest(serializedDataForRequest);
    std::string response = requestHandler->receiveResponse();
    std::cout<<"Response : "<<response<<std::endl;
}

void EmployeeInterface::viewTodayMenu(){
    Operation operation = Operation::GetTodaysMenu;
    std::string viewTodaysMenuSerializedRequest = SerializationUtility::serializeOperation(operation, "");
    requestHandler->sendRequest(viewTodaysMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

    std::cout<<"serializedMenuList"<<serializedMenuList<<std::endl;

    std::vector<std::string>MenuList = SerializationUtility::deserializeStringToVector(serializedMenuList);

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<MenuItem>(item);
        std::cout << "Menu Item Details:" << std::endl
          << "ID: " << menuItem.menuItemId << std::endl
          << "Name: " << menuItem.menuItemName << std::endl
          << "Type: " << static_cast<int>(menuItem.menuItemType) << std::endl
          << "Price: " << menuItem.price << std::endl;
        std::cout << std::endl;
    }
}

void EmployeeInterface::provideFeedbackForTodayMenu(){
    Operation operation = Operation::ProvideFeedback;
    Feedback feedback;
    std::cout<<"Provide Feeback "<<std::endl;
    feedback.userId = this->userIdLoggedIn;
    std::cout << "Enter Menu Item ID: ";
    std::cin >> feedback.menuItemId;
    
    std::cout << "Enter Rating: ";
    std::cin >> feedback.rating;
    
    std::cout << "Enter Comment: ";
    std::cin.ignore();
    std::getline(std::cin, feedback.comment);
    

    feedback.date = getCurrentTimestamp();

    std::string serializedData = SerializationUtility::serialize(feedback);
    std::string serializedDataForRequest = SerializationUtility::serializeOperation(operation, serializedData);

    requestHandler->sendRequest(serializedDataForRequest);
}


std::string EmployeeInterface::getCurrentTimestamp(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm;
#ifdef _WIN32
    localtime_s(&now_tm, &now_time_t); // Use localtime_s on Windows
#else
    localtime_r(&now_time_t, &now_tm); // Use localtime_r on POSIX-compliant systems
#endif
    
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}

void EmployeeInterface::voteForTomorrowMenu(){
    Operation operation = Operation::VoteItemFromTomorrowMenu;
    std::cout<<"Provide MenuItem Id you want to vote for: \n";
    int menuItemId;
    std::cin>>menuItemId;
    std::string menuItemIdStr =  std::to_string(menuItemId);
    auto voteForTomorrowItemSerializedRequest = SerializationUtility::serializeOperation(operation,menuItemIdStr);
    requestHandler->sendRequest(voteForTomorrowItemSerializedRequest);
}



void EmployeeInterface::showChefRollOutMenu(){
    Operation operation = Operation::GetChefRollOutMenuForTomorrow;
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(operation, std::to_string(this->userIdLoggedIn));
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

    std::vector<std::string>MenuList = SerializationUtility::deserializeStringToVector(serializedMenuList);

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);

        std::cout << "Menu Item Details:" << std::endl
          << "Menu Item ID: " << menuItem.menuItemId << "\t"
          << "Menu Item Name: " << menuItem.menuItemName << "\t"
          << "Menu Item Type: " << static_cast<int>(menuItem.menuItemType) << "\t"
          << "Price: " << menuItem.price << "\t"
          << "Average Rating: " << menuItem.averageRating << "\t"
          << "Sentiment Score: " << menuItem.sentiments << std::endl;
    }
}

void EmployeeInterface::viewNotification(){
    Operation operation = Operation::ViewNotification;
    std::string viewNotificationSerializedRequest = SerializationUtility::serializeOperation(operation, "");
    requestHandler->sendRequest(viewNotificationSerializedRequest);

    std::string serializedNotificationList = requestHandler->receiveResponse();

    std::vector<std::string>notificationList = SerializationUtility::deserializeStringToVector(serializedNotificationList);

    for (const auto& item : notificationList) {
        auto notification = SerializationUtility::deserialize<Notification>(item);
        std::cout << "Notification Details:" << std::endl
          << "ID: " << notification.notificationId << std::endl
          << "Title: " << notification.notificationTitle << std::endl
          << "Message: " << notification.message << std::endl
          << "Date: " << notification.date << std::endl;
        
    }
}