#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include "vectorSerializer.h"

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

class RequestHandler {
public:
    RequestHandler(int clientSocket, struct sockaddr_in serv_addr);
    void sendRequest(std::vector<std::string> request);
    std::vector<std::string> receiveResponse();
private:
    int clientSocket;
    struct sockaddr_in serv_addr;
    VectorSerializer vectorSerializer;
};

#endif // REQUESTHANDLER_H
