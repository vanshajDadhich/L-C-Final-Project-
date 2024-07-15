#ifndef IUSERCONTROLLER_H
#define IUSERCONTROLLER_H

#include <vector>
#include <string>
#include "../../../common/DTO/serializationUtility.h"
#include "../service/menuItemService.h"
#include "../service/nextDayMenuVotingService.h"
#include "../service/feedbackService.h"
#include "../service/todayMenuService.h"
#include "../service/notificationService.h"
#include "../service/userService.h"
#include "../service/userProfileService.h"
#include "../service/discardMenuItemDetailedFeedbackService.h"

class IUserController
{
public:
    virtual std::string handleRequest(Operation operation, const std::string& request) = 0;
};

#endif