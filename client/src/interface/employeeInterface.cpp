#include "../../inc/interface/employeeInterface.h"
#include "../../../common/utility/utility.h"
#include <iostream>
#include <vector>
#include <algorithm>

EmployeeInterface::EmployeeInterface(RequestHandler* requestHandler, int userIdLoggedIn)
    : requestHandler(requestHandler), userIdLoggedIn(userIdLoggedIn) {}

void EmployeeInterface::showMenu() {
    std::cout << "Welcome Employee\n\n";
    bool flag = true;
    while (flag) {
        std::cout << "Select the operation you would like to perform:\n"
                     "1. View Notification\n"
                     "2. View Chef Roll Out Menu For Tomorrow\n"
                     "3. Today's Menu\n"
                     "4. Provide Detailed Feedback for Discarded Menu Item\n"
                     "5. Update Profile\n"
                     "6. Exit\n"<< std::endl;

        int employeeChoice = Utility::getValidatedChoice(1, 6);

        if (employeeChoice == 1) {
            viewNotification();
        } else if (employeeChoice == 2) {
            showChefRollOutMenu();
        } else if (employeeChoice == 3) {
            viewTodayMenu();
        } else if (employeeChoice == 4) {
            getDetailedFeedbackForDiscardedMenuItem();
        } else if (employeeChoice == 5) {
            updateProfile();
        } else if (employeeChoice == 6) {
            flag = false;
        } else {
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}

void EmployeeInterface::viewNotification() {
    std::string viewNotificationSerializedRequest = SerializationUtility::serializeOperation(Operation::ViewNotification, "");
    requestHandler->sendRequest(viewNotificationSerializedRequest);

    std::string serializedNotificationList = requestHandler->receiveResponse();

    std::vector<std::string> notificationList = SerializationUtility::deserializeStringToVector(serializedNotificationList);

    for (const auto& item : notificationList) {
        auto notification = SerializationUtility::deserialize<Notification>(item);
        std::cout << "Notification Details:" << std::endl
                  << "Title: " << notification.notificationTitle << std::endl
                  << "Message: " << notification.message << std::endl
                  << "Date: " << notification.date << std::endl;
    }
}

void EmployeeInterface::showChefRollOutMenu() {
    std::vector<int> recommendedMenuItemIdsFromChef;
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::GetChefRollOutMenuForTomorrow, std::to_string(this->userIdLoggedIn));
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string response = requestHandler->receiveResponse();

    if (response == "0") {
        std::cout << "**********Menu is not yet rolled out by chef for the next day**********" << std::endl;
        return;
    }

    std::vector<std::string> MenuList = SerializationUtility::deserializeStringToVector(response);
    std::cout << "***************Chef's Recommended Menu for Tomorrow*************** \n";

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);
        recommendedMenuItemIdsFromChef.push_back(menuItem.menuItemId);
        std::cout << "Menu Item ID: " << menuItem.menuItemId << "\t"
                  << "Menu Item Name: " << menuItem.menuItemName << "\t"
                  << "Menu Item Type: " << Utility::getMenuItemType(menuItem.menuItemType) << "\t"
                  << "Price: " << menuItem.price << "\t"
                  << "Average Rating: " << menuItem.averageRating << "\t"
                  << "Sentiment Score: " << menuItem.sentiments << std::endl;
    }

    while (true) {
        std::cout << "Would you like to cast your vote for any item from the Chef's Recommended Menu? (Y/N) \n";
        char voteChoice;
        std::cin >> voteChoice;
        if (voteChoice == 'Y' || voteChoice == 'y') {
            voteForTomorrowMenu(recommendedMenuItemIdsFromChef);
        } else if (voteChoice == 'N' || voteChoice == 'n') {
            break;
        } else {
            std::cout << "Invalid Choice\n";
        }
    }
}

void EmployeeInterface::voteForTomorrowMenu(std::vector<int>& recommendedMenuItemIdsFromChef) {
    std::cout << "Enter the Menu Item ID you want to vote for: \n";
    int menuItemId;
    std::cin >> menuItemId;
    if (std::find(recommendedMenuItemIdsFromChef.begin(), recommendedMenuItemIdsFromChef.end(), menuItemId) == recommendedMenuItemIdsFromChef.end()) {
        std::cout << "Invalid Menu Item Id\n";
        return;
    }
    std::string menuItemIdStr = std::to_string(menuItemId);
    auto voteForTomorrowItemSerializedRequest = SerializationUtility::serializeOperation(Operation::VoteItemFromTomorrowMenu, menuItemIdStr);
    requestHandler->sendRequest(voteForTomorrowItemSerializedRequest);
    std::cout << requestHandler->receiveResponse() << std::endl;
}

void EmployeeInterface::viewTodayMenu() {
    std::vector<int> todaysMenuItemIds;
    std::string viewTodaysMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::GetTodaysMenu, "");
    requestHandler->sendRequest(viewTodaysMenuSerializedRequest);

    std::string response = requestHandler->receiveResponse();

    if (response == "0") {
        std::cout << "**********Menu is Not yet Published By Chef for today**********" << std::endl;
        return;
    }

    std::vector<std::string> MenuList = SerializationUtility::deserializeStringToVector(response);
    std::cout << "***************Today's Menu*************** \n";

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<MenuItem>(item);
        todaysMenuItemIds.push_back(menuItem.menuItemId);
        std::cout << "Menu Item Details:" << std::endl
                  << "ID: " << menuItem.menuItemId << std::endl
                  << "Name: " << menuItem.menuItemName << std::endl
                  << "Type: " << Utility::getMenuItemType(menuItem.menuItemType) << std::endl
                  << "Price: " << menuItem.price << std::endl;
        std::cout << std::endl;
    }

    while (true) {
        std::cout << "Would you like to provide feedback for any item from today's Menu? (Y/N) \n";
        char feedbackChoice;
        std::cin >> feedbackChoice;
        if (feedbackChoice == 'Y' || feedbackChoice == 'y') {
            provideFeedbackForTodayMenu(todaysMenuItemIds);
        } else if (feedbackChoice == 'N' || feedbackChoice == 'n') {
            break;
        } else {
            std::cout << "Invalid Choice\n";
        }
    }
}

void EmployeeInterface::provideFeedbackForTodayMenu(std::vector<int>& menuItemIdsFromTodayMenu) {
    Feedback feedback;
    std::cout << "Enter the Menu Item Id you want to Provide the Feedback for: " << std::endl;
    feedback.userId = this->userIdLoggedIn;
    std::cin >> feedback.menuItemId;

    if (std::find(menuItemIdsFromTodayMenu.begin(), menuItemIdsFromTodayMenu.end(), feedback.menuItemId) == menuItemIdsFromTodayMenu.end()) {
        std::cout << "Invalid Menu Item Id\n";
        return;
    }

    std::cout << "Enter Rating: ";
    std::cin >> feedback.rating;

    std::cout << "Enter Comment: ";
    std::cin.ignore();
    std::getline(std::cin, feedback.comment);

    feedback.date = "";

    std::string serializedData = SerializationUtility::serialize(feedback);
    std::string serializedDataForRequest = SerializationUtility::serializeOperation(Operation::ProvideFeedback, serializedData);

    requestHandler->sendRequest(serializedDataForRequest);
    std::cout << requestHandler->receiveResponse() << std::endl;
}

void EmployeeInterface::getDetailedFeedbackForDiscardedMenuItem() {
    DiscardMenuItemDetailedFeedback discardMenuItemDetailedFeedback;
    discardMenuItemDetailedFeedback.userId = this->userIdLoggedIn;
    std::cout << "Provide MenuItem Id you want to provide detailed feedback for: \n";
    std::cin >> discardMenuItemDetailedFeedback.menuItemId;
    std::cout << "What did you like about the menu item? \n";
    std::cin.ignore();
    std::getline(std::cin, discardMenuItemDetailedFeedback.whatYouLiked);
    std::cout << "How Would you like this food Item to taste? \n";
    std::getline(std::cin, discardMenuItemDetailedFeedback.howWouldItTaste);
    std::cout << "Share your mom's recipe. \n";
    std::getline(std::cin, discardMenuItemDetailedFeedback.shareRecipe);
    std::cout<<"[EmployeeController] Discard Menu Item Detailed Feedback Received\n"<<discardMenuItemDetailedFeedback.whatYouLiked<<"\n"<<discardMenuItemDetailedFeedback.howWouldItTaste<<"\n"<<discardMenuItemDetailedFeedback.shareRecipe<<"\n";
    std::string serializedData = SerializationUtility::serialize(discardMenuItemDetailedFeedback);
    std::string serializedDataForRequest = SerializationUtility::serializeOperation(Operation::ProvideDiscardMenuItemDetailedFeedback, serializedData);
    requestHandler->sendRequest(serializedDataForRequest);
    std::cout << requestHandler->receiveResponse() << std::endl;
}

void EmployeeInterface::updateProfile(){
    UserProfile userProfile;
    userProfile.userId = this->userIdLoggedIn;

    std::cout << "Enter vegetarian preference (1 for Vegetarian, 2 for Non Vegetarian, 3 for Eggetarian): " << std::endl;
    int vegetarianPreferenceInt;
    std::cin >> vegetarianPreferenceInt;
    userProfile.vegetarianPreference = static_cast<VegetarianPreference>(vegetarianPreferenceInt);

    std::cout << "Enter spice level option (1 for High, 2 for Medium, 3 for Low): " << std::endl;
    int spiceLevelOptionInt;
    std::cin >> spiceLevelOptionInt;
    userProfile.spiceLevelOption = static_cast<SpiceLevelOption>(spiceLevelOptionInt);

    std::cout << "Enter Cuisine Preference (1 for North Indian, 2 for South Indian, 3 for Other): " << std::endl;
    int cuisinePreferenceInt;
    std::cin >> cuisinePreferenceInt;
    userProfile.cuisinePreference = static_cast<CuisinePreference>(cuisinePreferenceInt);

    std::cout << "Enter sweet tooth preference (1 for Yes, 0 for No): " << std::endl;
    int sweetToothPreferenceInt;
    std::cin >> sweetToothPreferenceInt;
    userProfile.sweetToothPreference = static_cast<SweetToothPreference>(sweetToothPreferenceInt);

    std::string serializedData = SerializationUtility::serialize(userProfile);
    std::string serializedDataForRequest = SerializationUtility::serializeOperation(Operation::UpdateProfile, serializedData);
    requestHandler->sendRequest(serializedDataForRequest);
    std::cout << requestHandler->receiveResponse() << std::endl;
}