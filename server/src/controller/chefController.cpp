#include "../../inc/controller/chefController.h"

ChefController::ChefController() {}

std::vector<std::string> ChefController::handleRequest( std::vector<std::string> request) {
    std::vector<std::string> response;
    response.push_back("Chef Controller");
    return response;
}
