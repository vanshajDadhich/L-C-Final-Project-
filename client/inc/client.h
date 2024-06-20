#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <netinet/in.h>

class Client {
public:
    Client(const int& server_port);
    ~Client();
    bool connectToServer();
    void disconnect();
    int getSocket() const;
    struct sockaddr_in getAddress() const;

private:
    int server_port;
    int clientSocket;
    struct sockaddr_in serv_addr;
};

#endif // CLIENT_H
