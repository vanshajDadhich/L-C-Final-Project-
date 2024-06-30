#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <cstdint>
#include <string>
#include <sstream>
#include "serializable.h"

struct Notification : public Serializable {
    int notificationId;
    std::string notificationTitle;
    std::string message;
    std::string date;

    Notification(int notificationId = 0, std::string notificationTitle = "", std::string message = "", std::string date = "")
        : notificationId(notificationId), notificationTitle(notificationTitle), message(message), date(date) {}

    std::string serialize() const override {
        return std::to_string(notificationId) + ";" +
               notificationTitle + ";" +
               message + ";" +
               date;
    }

    void deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string token;

        std::getline(iss, token, ';');
        notificationId = std::stoi(token);

        std::getline(iss, token, ';');
        notificationTitle = token;

        std::getline(iss, token, ';');
        message = token;

        std::getline(iss, token, ';');
        date = token;
    }
};

#endif // NOTIFICATION_H
