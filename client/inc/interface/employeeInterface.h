#ifndef EMPLOYEEINTERFACE_H
#define EMPLOYEEINTERFACE_H

#include "IUserInterface.h"
#include <string>
#include <vector>

class EmployeeInterface : public IUserInterface {
public:
    EmployeeInterface(RequestHandler* requestHandler, int userIdLoggedIn);

    void showMenu() override;

private:
    RequestHandler* requestHandler;
    int userIdLoggedIn;
    
    void viewNotification();
    void showChefRollOutMenu();
    void voteForTomorrowMenu(std::vector<int>& recommendedMenuItemIdsFromChef);
    void viewTodayMenu();
    void updateProfile();
    void provideFeedbackForTodayMenu(std::vector<int>& menuItemIdsFromTodayMenu);
    void getDetailedFeedbackForDiscardedMenuItem();
};

#endif
