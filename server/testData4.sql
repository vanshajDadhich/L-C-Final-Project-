CREATE DATABASE IF NOT EXISTS databaseRecommendationEngine;
USE databaseRecommendationEngine;


-- CREATE TABLE IF NOT EXISTS todayMenu (
--     menuItemId BIGINT UNSIGNED NOT NULL,
--     PRIMARY KEY (menuItemId),
--     FOREIGN KEY (menuItemId) REFERENCES MenuItem(menuItemId)
-- );


-- ALTER TABLE Feedback
-- DROP FOREIGN KEY Feedback_ibfk_2;

-- ALTER TABLE Feedback
-- ADD CONSTRAINT Feedback_ibfk_2
-- FOREIGN KEY (MenuItemId) REFERENCES MenuItem(menuItemId)
-- ON DELETE CASCADE;

CREATE TABLE Notification (
    notificationId INT AUTO_INCREMENT PRIMARY KEY,
    notificationTitle VARCHAR(255) NOT NULL,
    message TEXT NOT NULL,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
