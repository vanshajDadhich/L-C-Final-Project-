#ifndef INOTIFICATION_DAO_H
#define INOTIFICATION_DAO_H

#include "../DTO/notification.h"
#include <vector>

class INotificationDAO {
public:
    virtual std::vector<Notification> getAllNotifications() = 0;

    virtual Notification getNotificationById(const int& notificationId) = 0;

    virtual bool addNotification(const Notification& notification) = 0;
    
    virtual bool deleteNotification(const int& notificationId) = 0;

    virtual std::vector<Notification> getAllNotificationsFromId(const int& notificationId) = 0;
};

#endif // INOTIFICATION_DAO_H
