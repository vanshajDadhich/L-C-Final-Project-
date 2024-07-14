#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <netinet/in.h>
#include "../../../common/exception/inc/socketException.h"

class RequestHandler {
public:
    RequestHandler(int clientSocket, struct sockaddr_in serv_addr);
    void sendRequest(const std::string& request);
    std::string receiveResponse();

private:
    int clientSocket;
    struct sockaddr_in serv_addr;
};

#endif
