#include "../inc/userInterface.h"
#include <iostream>

#include<vector>


UserInterface::UserInterface(Client& client)
    : client(client), requestHandler(nullptr) {}

void UserInterface::run() {
    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server" << std::endl;
        return;
    }

    requestHandler = new RequestHandler(client.getSocket(), client.getAddress());
    handleUserInput();

    delete requestHandler;
    client.disconnect();
}

void UserInterface::handleUserInput() {
    int userId;
    std::string password;
    std::cout << "Enter Login Credantials: \n";
    std::cout<<"UserId : ";
    std::cin>>userId;
    std::cout<<"Password : ";
    std::cin>>password;
    int operation = Operation::login;

    requestHandler->sendRequest({std::to_string(operation), std::to_string(userId), password} ) ;
    std::vector<std::string> response = requestHandler->receiveResponse();
    std::cout << "Server: " << response[0]<< std::endl;
}
