#include"../../inc/service/notificationService.h"

NotificationService::NotificationService(std::shared_ptr<NotificationDAO> notificationDAO)
    : notificationDAO(std::move(notificationDAO)) {}


bool NotificationService::addNotification(const Notification& notification) {
    return notificationDAO->addNotification(notification);
}

bool NotificationService::deleteNotificationByID(int notificationId) {
    return notificationDAO->deleteNotification(notificationId);
}

Notification NotificationService::getNotificationById(int notificationId) {
    return notificationDAO->getNotificationById(notificationId);
}

std::vector<Notification> NotificationService::getAllNotifications() {
    return notificationDAO->getAllNotifications();
}

std::vector<Notification> NotificationService::getNotificationsFromId(const int& notificationId) {
    return notificationDAO->getAllNotificationsFromId(notificationId);
}
