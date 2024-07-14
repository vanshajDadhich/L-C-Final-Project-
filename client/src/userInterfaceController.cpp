#include "../inc/userInterfaceController.h"
#include <iostream>

UserInterfaceController::UserInterfaceController(Client& client)
    : client(client), requestHandler(nullptr) {}

void UserInterfaceController::run() {
    client.connectToServer();

    requestHandler = new RequestHandler(client.getSocket(), client.getAddress());
    handleUserInput();

    delete requestHandler;
    client.disconnect();
}

void UserInterfaceController::loginPrompt() {
    Login login;
    std::cout << "Enter Login Credentials:\n";
    std::cout << "UserId: ";
    std::cin >> login.userId;
    std::cout << "Password: ";
    std::cin >> login.password;
    auto loginData = SerializationUtility::serialize(login);
    this->userIdLoggedIn = login.userId;
    auto loginSerializedRequest = SerializationUtility::serializeOperation(Operation::LoginUser, loginData);

    requestHandler->sendRequest(loginSerializedRequest);
}

void UserInterfaceController::handleUserInput() {
    const int maxRetries = 3;
    std::string response;
    Role userRole;

    for (int retryCount = 0; retryCount < maxRetries; retryCount++) {
        loginPrompt();
        response = requestHandler->receiveResponse();

        try {
            userRole = static_cast<Role>(std::stoi(response));

            if (userRole == Role::Admin || userRole == Role::Chef || userRole == Role::Employee) {
                initializeUserInterface(userRole);
                userInterface->showMenu();
                return; 
            } else {
                throw std::invalid_argument("Invalid login Credentials");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << ". Please try again.\n";
        }

        std::cout << "Attempt " << retryCount + 1 << " of " << maxRetries << "\n";
    }

    std::cerr << "Maximum login attempts exceeded. Exiting.\n";
}

void UserInterfaceController::initializeUserInterface(Role userRole) {
    if (userRole == Role::Admin) {
        this->userInterface = new AdminInterface(requestHandler);
    } else if (userRole == Role::Employee) {
        this->userInterface = new EmployeeInterface(requestHandler, this->userIdLoggedIn);
    } else {
        this->userInterface = new ChefInterface(requestHandler);
    }
}
