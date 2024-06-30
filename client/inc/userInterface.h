#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include "client.h"
#include "requestHandler.h"
#include "./DTO/login.h"
#include "./DTO/feedback.h"
#include "./DTO/user.h"
#include "./DTO/menuItem.h"
#include "./DTO/SerializationUtility.h"
#include "./DTO/nextDayMenuRollOut.h"
#include "./DTO/notification.h"

class UserInterface {
public:
    UserInterface(Client& client);
    void run();

private:
    Client& client;
    RequestHandler* requestHandler;
    int userIdLoggedIn;

    void handleUserInput();
    void showMenuPrompt(std::string userRole);
    int showAdminMenu();
    void showAddItemPrompt();
    void showUpdateMenuPrompt();
    void showDeleteItemPrompt();
    void showMenu();
    void addUserPrompt();
    void showChefMenu();
    void showRecommendedMenu(MenuItemType menuItemType);
    void rollOutMenuForTomorrow();
    void publishMenuForToday();
    void selectMealTypeForRecommendationMenu();
    void showEmployeeMenu();
    void loginPrompt();
    std::vector<std::string> getDataToUpdate();
    void viewNotification();
    void showChefRollOutMenu();
    void viewTodayMenu();
    void voteForTomorrowMenu();
    void provideFeedbackForTodayMenu();
    std::string getCurrentTimestamp();
};

#endif 