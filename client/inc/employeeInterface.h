#ifndef EMPLOYEEINTERFACE_H
#define EMPLOYEEINTERFACE_H

#include "IUserInterface.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>

class EmployeeInterface : public IUserInterface {
private:
    RequestHandler* requestHandler;
    int userIdLoggedIn;

    void viewNotification();
    void showChefRollOutMenu();
    void voteForTomorrowMenu();
    void viewTodayMenu();
    void provideFeedbackForTodayMenu();
    std::string getCurrentTimestamp();

public:
    EmployeeInterface(RequestHandler* requestHandler, int userIdLoggedIn);

    void showMenu() override;
};

#endif
