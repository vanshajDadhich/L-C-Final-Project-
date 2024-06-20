#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>
#include <memory>
#include <netinet/in.h>
#include <mutex>
#include <atomic>
#include "clientHandler.h"

class Server {
public:
    Server(int port);
    ~Server();
    void start();
    void stop();

private:
    int port;
    int server_fd;
    struct sockaddr_in address;
    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;
    std::mutex clientsMutex;
    std::atomic<bool> running;

    void acceptClients();
};

#endif // SERVER_H
