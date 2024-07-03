#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <netinet/in.h>
#include "socketException.h"

class RequestHandler {
public:
    RequestHandler(int clientSocket, struct sockaddr_in serv_addr);
    void sendRequest(const std::string& request);
    std::string receiveResponse();

private:
    int clientSocket;
    struct sockaddr_in serv_addr;
    void handleError(const std::string& errorMessage) const;
};

#endif // REQUESTHANDLER_H
