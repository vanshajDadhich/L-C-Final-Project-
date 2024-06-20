#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

#include <string>
#include <vector>
#include "../controller/authenticationController.h"


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
   GiveFeedback = 9,
   SelectItem = 10,
   login = 11
};

class RequestProcessor {
    private :
    AuthenticationController* authenticationController;
public:
    RequestProcessor();
    std::vector<std::string> processRequest(std::vector<std::string> request);
};

#endif // REQUESTPROCESSOR_H
