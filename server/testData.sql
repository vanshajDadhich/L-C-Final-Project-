CREATE DATABASE databaseRecommendationEngine;

USE databaseRecommendationEngine;

CREATE TABLE IF NOT EXISTS MenuItem(
    menuItemId BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    menuItemName VARCHAR(255) NOT NULL,
    menuItemType INT NOT NULL,  -- Changed to INT
    Availability BOOLEAN NOT NULL,
    Price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE IF NOT EXISTS User(
    userId BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    userName VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL,
    Role INT NOT NULL  -- Changed to INT
);

CREATE TABLE IF NOT EXISTS Feedback(
    feedbackId BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    userId BIGINT UNSIGNED NOT NULL,
    MenuItemId BIGINT UNSIGNED NOT NULL,
    Rating INT NOT NULL,
    comment VARCHAR(255) NOT NULL,
    timestamp DATE NOT NULL,
    FOREIGN KEY (userId) REFERENCES User(userId),
    FOREIGN KEY (MenuItemId) REFERENCES MenuItem(menuItemId)
);

CREATE TABLE IF NOT EXISTS RecommendationSelection(
    id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    menuItemId BIGINT UNSIGNED NOT NULL,
    selectionCount BIGINT NOT NULL,
    sentimentScore BIGINT NOT NULL,
    FOREIGN KEY (menuItemId) REFERENCES MenuItem(menuItemId)
);

INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, Availability, Price) VALUES
(1, 'Masala Dosa', 1, true, 6.99),          -- Breakfast is 1
(2, 'Aloo Paratha', 1, true, 5.49),         -- Breakfast is 1
(3, 'Paneer Butter Masala', 2, true, 8.99), -- Lunch is 2
(4, 'Chole Bhature', 2, true, 7.49),        -- Lunch is 2
(5, 'Chicken Biryani', 2, true, 10.99),     -- Lunch is 2
(6, 'Rogan Josh', 3, true, 12.99),          -- Dinner is 3
(7, 'Butter Chicken', 3, true, 11.49),      -- Dinner is 3
(8, 'Palak Paneer', 3, true, 9.99),         -- Dinner is 3
(9, 'Idli Sambar', 1, true, 4.99),          -- Breakfast is 1
(10, 'Lamb Vindaloo', 3, true, 13.99);      -- Dinner is 3

INSERT INTO User (userId, userName, password, Role) VALUES
(1, 'john_doe', 'password123', 1),     -- Admin is 1
(2, 'jane_smith', 'securepass456', 2), -- Employee is 2
(3, 'chef_ravi', 'delicious789', 2),   -- Employee is 2
(4, 'employee_mike', 'workhard101', 3),-- chef is 3
(5, 'employee_susan', 'greatjob202', 3),-- chef is 3
(6, 'admin_anna', 'adminpass303', 1),  -- Admin is 1
(7, 'chef_kumar', 'tastyfood404', 2),  -- Employee is 2
(8, 'employee_johnny', 'service505', 3),-- Chef is 3
(9, 'admin_sam', 'manager606', 1),     -- Admin is 1
(10, 'chef_alia', 'spicy707', 2);      -- Employee is 2

INSERT INTO Feedback (feedbackId, userId, MenuItemId, Rating, comment, timestamp) VALUES
(1, 1, 1, 5, 'Delicious and perfect!', '2024-06-01'),
(2, 2, 3, 4, 'Very tasty, but a bit too spicy.', '2024-06-02'),
(3, 3, 5, 3, 'It was okay, nothing special.', '2024-06-03'),
(4, 4, 2, 5, 'Absolutely loved it!', '2024-06-04'),
(5, 5, 4, 4, 'Good but could use more seasoning.', '2024-06-05'),
(6, 6, 6, 5, 'Amazing dish, highly recommend!', '2024-06-06'),
(7, 7, 8, 4, 'Pretty good, will order again.', '2024-06-07'),
(8, 8, 7, 5, 'Fantastic flavor, well cooked.', '2024-06-08'),
(9, 9, 9, 3, 'Average, expected more.', '2024-06-09'),
(10, 10, 10, 5, 'Perfectly sweet and delightful!', '2024-06-10');

INSERT INTO RecommendationSelection (id, menuItemId, selectionCount, sentimentScore) VALUES
(1, 1, 150, 4.5),
(2, 2, 120, 4.2),
(3, 3, 200, 4.8),
(4, 4, 175, 4.1),
(5, 5, 110, 3.9),
(6, 6, 140, 4.3),
(7, 7, 160, 4.7),
(8, 8, 130, 4.0),
(9, 9, 155, 4.4),
(10, 10, 180, 4.6);
