#ifndef NOTIFICATION_DAO_H
#define NOTIFICATION_DAO_H

#include "INotificationDAO.h"
#include "databaseConnection.h"
#include <memory>
#include <vector>

class NotificationDAO : public INotificationDAO {
public:
    NotificationDAO();
    std::vector<Notification> getAllNotifications();
    Notification getNotificationById(const int& notificationId);
    bool addNotification(const Notification& notification);
    bool deleteNotification(const int& notificationId);
    std::vector<Notification> getAllNotificationsFromId(const int& notificationId);

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif