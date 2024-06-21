#ifndef IUSERCONTROLLER_H
#define IUSERCONTROLLER_H

#include <vector>
#include <string>

enum Operation : int {
   AddUser = 0,
   AddMenuItem = 1,
   DeleteMenuItem = 2,
   UpdateMenuItem = 3,
   ViewMenu = 4,
   RollOutMenuForNextDay = 5,
   GenerateReport = 6,
   PublishMenuForToday = 7,
   ViewNotification = 8,
   GetMenuAndProvideFeedback = 9,
   SelectItemFromTomorrowMenu = 10,
   login = 11
};



class IUserController
{
public:
    virtual std::vector<std::string> handleRequest(std::vector<std::string> request) = 0;

};

#endif // IUSERCONTROLLER_H