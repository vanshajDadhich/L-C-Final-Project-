#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include "../../inc/DAO/notificationDAO.h"

#include<memory>

class NotificationService
{
public:
    NotificationService(std::shared_ptr<NotificationDAO> notificationDAO);
    bool addNotification(const Notification& notification);
    bool deleteNotificationByID(int notificationId);
    Notification getNotificationById(int notificationId);
    std::vector<Notification> getNotificationsFromId(const int& notificationId);
    std::vector<Notification> getAllNotifications();
    ~NotificationService() = default;
private:
    std::shared_ptr<NotificationDAO> notificationDAO;
};

#endif
