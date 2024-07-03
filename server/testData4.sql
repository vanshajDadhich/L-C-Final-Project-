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

-- CREATE TABLE Notification (
--     notificationId INT AUTO_INCREMENT PRIMARY KEY,
--     notificationTitle VARCHAR(255) NOT NULL,
--     message TEXT NOT NULL,
--     date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
-- );


-- INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, Availability, Price) VALUES
-- (19, 'Spicy Chicken Wings', 3, true, 11.49),       -- Dinner (non-veg)


-- -- Insert bad ratings with comments
-- INSERT INTO Feedback (feedbackId, userId, MenuItemId, Rating, comment, timestamp) VALUES
-- (80, 3, 1, 1, 'Masala Dosa was burnt and inedible.', '2024-08-16'),
-- (81, 4, 5, 1, 'Chicken Biryani was extremely dry and overcooked.', '2024-08-17'),
-- (82, 6, 7, 1, 'Butter Chicken had a weird aftertaste and was too oily.', '2024-08-18'),
-- (83, 7, 9, 1, 'Idli Sambar was cold and lacked flavor.', '2024-08-19'),
-- (84, 8, 11, 1, 'Egg Benedict was undercooked and the sauce was bland.', '2024-08-20'),
-- (85, 9, 13, 1, 'Pulao was undercooked and tasteless.', '2024-08-21'),
-- (86, 10, 15, 1, 'Fish Tacos were soggy and the fish was not fresh.', '2024-08-22'),
-- (87, 1, 17, 1, 'Vegetable Biryani was mushy and had no taste.', '2024-08-23'),
-- (88, 2, 18, 1, 'Chocolate Cake was dry and not sweet enough.', '2024-08-24'),
-- (90, 4, 20, 1, 'Fruit Salad was old and not fresh at all.', '2024-08-26');

-- -- Create the discardMenuItemDetailedFeedback table
-- CREATE TABLE discardMenuItemDetailedFeedback (
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     userId BIGINT UNSIGNED,
--     menuItemId BIGINT UNSIGNED,
--     whatYouLiked VARCHAR(255),
--     howWouldItTaste VARCHAR(255),
--     shareRecipe VARCHAR(255),
--     FOREIGN KEY (userId) REFERENCES User(userId) ON DELETE CASCADE,
--     FOREIGN KEY (menuItemId) REFERENCES MenuItem(menuItemId) ON DELETE CASCADE
-- );

-- -- Create the UserProfile table
-- CREATE TABLE UserProfile (
--     userId BIGINT UNSIGNED PRIMARY KEY,
--     vegetarianPreference INT,
--     spiceLevelOption INT,
--     foodPreference INT,
--     sweetToothPreference INT,
--     FOREIGN KEY (userId) REFERENCES User(userId) ON DELETE CASCADE
-- );

-- Clear the existing data from MenuItem table
DELETE FROM MenuItem;

-- Adding columns to MenuItem table
ALTER TABLE MenuItem
ADD COLUMN vegetarianPreference INT,
ADD COLUMN spiceLevelOption INT,
ADD COLUMN foodPreference INT,
ADD COLUMN sweetToothPreference INT;

-- Inserting new menu items with updated columns
INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, Availability, Price, vegetarianPreference, spiceLevelOption, foodPreference, sweetToothPreference) VALUES
(1, 'Masala Dosa', 1, true, 6.99, 1, 3, 2, 0),          -- Breakfast, Vegetarian, High Spice, South Indian, No Sweet
(2, 'Aloo Paratha', 1, true, 5.49, 1, 2, 1, 0),         -- Breakfast, Vegetarian, Medium Spice, North Indian, No Sweet
(3, 'Paneer Butter Masala', 2, true, 8.99, 1, 2, 1, 0), -- Lunch, Vegetarian, Medium Spice, North Indian, No Sweet
(4, 'Chole Bhature', 2, true, 7.49, 1, 2, 1, 0),        -- Lunch, Vegetarian, Medium Spice, North Indian, No Sweet
(5, 'Chicken Biryani', 2, true, 10.99, 2, 3, 1, 0),     -- Lunch, Non-Vegetarian, High Spice, North Indian, No Sweet
(6, 'Rogan Josh', 3, true, 12.99, 2, 3, 1, 0),          -- Dinner, Non-Vegetarian, High Spice, North Indian, No Sweet
(7, 'Butter Chicken', 3, true, 11.49, 2, 2, 1, 0),      -- Dinner, Non-Vegetarian, Medium Spice, North Indian, No Sweet
(8, 'Palak Paneer', 3, true, 9.99, 1, 2, 1, 0),         -- Dinner, Vegetarian, Medium Spice, North Indian, No Sweet
(9, 'Idli Sambar', 1, true, 4.99, 1, 2, 2, 0),          -- Breakfast, Vegetarian, Medium Spice, South Indian, No Sweet
(10, 'Lamb Vindaloo', 3, true, 13.99, 2, 3, 1, 0),      -- Dinner, Non-Vegetarian, High Spice, North Indian, No Sweet
(11, 'Egg Benedict', 1, true, 7.99, 3, 1, 3, 0),        -- Breakfast, Eggetarian, Low Spice, Other, No Sweet
(12, 'Pancakes', 1, true, 5.99, 1, 1, 3, 1),            -- Breakfast, Vegetarian, Low Spice, Other, Sweet
(13, 'Pulao', 2, true, 8.49, 1, 2, 1, 0),               -- Lunch, Vegetarian, Medium Spice, North Indian, No Sweet
(14, 'Chicken Curry', 2, true, 9.99, 2, 3, 1, 0),       -- Lunch, Non-Vegetarian, High Spice, North Indian, No Sweet
(15, 'Fish Tacos', 2, true, 10.49, 2, 2, 3, 0),         -- Lunch, Non-Vegetarian, Medium Spice, Other, No Sweet
(16, 'Steak', 3, true, 15.99, 2, 3, 3, 0),              -- Dinner, Non-Vegetarian, High Spice, Other, No Sweet
(17, 'Vegetable Biryani', 2, true, 9.49, 1, 3, 1, 0),   -- Lunch, Vegetarian, High Spice, North Indian, No Sweet
(18, 'Chocolate Cake', 3, true, 6.99, 1, 1, 3, 1),      -- Dinner, Vegetarian, Low Spice, Other, Sweet
(19, 'Spicy Chicken Wings', 3, true, 11.49, 2, 3, 3, 0),-- Dinner, Non-Vegetarian, High Spice, Other, No Sweet
(20, 'Fruit Salad', 1, true, 4.99, 1, 1, 3, 1);         -- Breakfast, Vegetarian, Low Spice, Other, Sweet
