USE databaseRecommendationEngine;

-- Insert additional MenuItems
INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, Availability, Price) VALUES
(11, 'Egg Benedict', 1, true, 7.99),              -- Breakfast (non-veg)
(21, 'Pancakes', 1, true, 5.99),                   -- Breakfast (sweet)
(13, 'Pulao', 2, true, 8.49),                      -- Lunch (veg)
(14, 'Chicken Curry', 2, true, 9.99),              -- Lunch (non-veg)
(15, 'Fish Tacos', 2, true, 10.49),                -- Lunch (non-veg)
(16, 'Steak', 3, true, 15.99),                     -- Dinner (non-veg)
(17, 'Vegetable Biryani', 2, true, 9.49),          -- Lunch (veg)
(18, 'Chocolate Cake', 3, true, 6.99),             -- Dinner (sweet)
(19, 'Spicy Chicken Wings', 3, true, 11.49),       -- Dinner (non-veg)
(20, 'Fruit Salad', 1, true, 4.99);                -- Breakfast (sweet)

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
(10, 10, 10, 5, 'Perfectly sweet and delightful!', '2024-06-10'),
(11, 1, 11, 4, 'Eggs were cooked perfectly, but could use more seasoning.', '2024-06-11'),
(12, 2, 12, 5, 'Pancakes were fluffy and delicious, loved the syrup!', '2024-06-12'),
(13, 3, 13, 3, 'Pulao was okay, needed more vegetables.', '2024-06-13'),
(14, 4, 14, 4, 'Delicious chicken curry, just the right amount of spice.', '2024-06-14'),
(15, 5, 15, 4, 'Tacos were good, fish was fresh.', '2024-06-15'),
(16, 6, 16, 5, 'Perfectly cooked steak, very tender.', '2024-06-16'),
(17, 7, 17, 3, 'Vegetable biryani was decent, could be more flavorful.', '2024-06-17'),
(18, 8, 18, 5, 'Chocolate cake was heavenly, loved it!', '2024-06-18'),
(19, 9, 19, 4, 'Spicy chicken wings were tasty, great appetizer.', '2024-06-19'),
(20, 10, 20, 5, 'Refreshing fruit salad, perfect for breakfast.', '2024-06-20'),
(21, 1, 13, 4, 'Pulao was delicious, loved the mix of spices.', '2024-06-21'),
(22, 2, 14, 5, 'Chicken curry was outstanding, a must-try!', '2024-06-22'),
(23, 3, 15, 3, 'Tacos were okay, expected more flavor.', '2024-06-23'),
(24, 4, 16, 4, 'Steak was excellent, perfectly grilled.', '2024-06-24'),
(25, 5, 17, 4, 'Vegetable biryani was tasty, good portion size.', '2024-06-25'),
(26, 6, 18, 5, 'Chocolate cake was divine, rich and moist.', '2024-06-26'),
(27, 7, 19, 3, 'Spicy chicken wings were too spicy for my taste.', '2024-06-27'),
(28, 8, 20, 4, 'Fresh fruit salad, loved the assortment of fruits.', '2024-06-28'),
(29, 9, 11, 3, 'Egg Benedict was alright, not very flavorful.', '2024-06-29'),
(30, 10, 12, 5, 'Best pancakes ever, fluffy and delicious!', '2024-06-30'),
(31, 1, 11, 5, 'Egg Benedict was amazing, loved the hollandaise sauce!', '2024-07-01'),
(32, 2, 12, 4, 'Pancakes were good, could be a bit crispier.', '2024-07-02'),
(33, 3, 13, 3, 'Pulao lacked seasoning, needs improvement.', '2024-07-03'),
(34, 4, 14, 3, 'Chicken curry was flavorful, but a bit too spicy.', '2024-07-04'),
(35, 5, 15, 5, 'Fish Tacos were superb, fresh and tasty.', '2024-07-05'),
(36, 6, 16, 4, 'Steak was good, could have been more tender.', '2024-07-06'),
(37, 7, 17, 3, 'Vegetable biryani was okay, could use more vegetables.', '2024-07-07'),
(38, 8, 18, 5, 'Chocolate cake was heavenly, loved every bite!', '2024-07-08'),
(39, 9, 19, 4, 'Spicy chicken wings were delicious, perfect level of spice.', '2024-07-09'),
(40, 10, 20, 5, 'Refreshing fruit salad, perfect for a summer day.', '2024-07-10'),
(41, 1, 1, 1, 'Masala Dosa was cold and lacked flavor.', '2024-07-11'),
(42, 2, 1, 5, 'Masala Dosa was fantastic, crispy and flavorful.', '2024-07-12'),
(43, 3, 2, 1, 'Aloo Paratha was too oily and bland.', '2024-07-13'),
(44, 4, 2, 5, 'Aloo Paratha was perfect, loved it!', '2024-07-14'),
(45, 5, 3, 2, 'Paneer Butter Masala was okay, but not great.', '2024-07-15'),
(46, 6, 3, 4, 'Paneer Butter Masala was delicious, creamy and rich.', '2024-07-16'),
(47, 7, 4, 1, 'Chole Bhature was awful, too salty.', '2024-07-17'),
(48, 8, 4, 5, 'Chole Bhature was amazing, just like home.', '2024-07-18'),
(49, 9, 5, 3, 'Chicken Biryani was average, expected more.', '2024-07-19'),
(50, 10, 5, 4, 'Chicken Biryani was good, nice spices.', '2024-07-20'),
(51, 1, 6, 1, 'Rogan Josh was too spicy and overcooked.', '2024-07-21'),
(52, 2, 6, 5, 'Rogan Josh was tender and perfectly spiced.', '2024-07-22'),
(53, 3, 7, 2, 'Butter Chicken was too sweet.', '2024-07-23'),
(54, 4, 7, 4, 'Butter Chicken was creamy and flavorful.', '2024-07-24'),
(55, 5, 8, 3, 'Palak Paneer was bland, needed more spices.', '2024-07-25'),
(56, 6, 8, 4, 'Palak Paneer was delicious, very flavorful.', '2024-07-26'),
(57, 7, 9, 1, 'Idli Sambar was dry and tasteless.', '2024-07-27'),
(58, 8, 9, 5, 'Idli Sambar was soft and delicious.', '2024-07-28'),
(59, 9, 10, 2, 'Lamb Vindaloo was too tough.', '2024-07-29'),
(60, 1, 10, 5, 'Lamb Vindaloo was tender and spicy.', '2024-07-30'),
(61, 1, 11, 1, 'Egg Benedict was undercooked.', '2024-07-31'),
(62, 2, 11, 5, 'Egg Benedict was perfect, loved the sauce.', '2024-08-01'),
(63, 3, 12, 2, 'Pancakes were too thick and dry.', '2024-08-02'),
(64, 4, 12, 5, 'Pancakes were fluffy and delicious.', '2024-08-03'),
(65, 5, 13, 1, 'Pulao lacked flavor and was undercooked.', '2024-08-04'),
(66, 6, 13, 4, 'Pulao was well-cooked and tasty.', '2024-08-05'),
(67, 7, 14, 1, 'Chicken Curry was too oily.', '2024-08-06'),
(68, 8, 14, 5, 'Chicken Curry was rich and flavorful.', '2024-08-07'),
(69, 9, 15, 3, 'Fish Tacos were okay, not very fresh.', '2024-08-08'),
(70, 10, 15, 4, 'Fish Tacos were fresh and tasty.', '2024-08-09'),
(71, 1, 16, 1, 'Steak was tough and overcooked.', '2024-08-10'),
(72, 2, 16, 5, 'Steak was tender and juicy.', '2024-08-11'),
(73, 3, 17, 2, 'Vegetable Biryani was bland.', '2024-08-12'),
(74, 4, 17, 4, 'Vegetable Biryani was flavorful and well-cooked.', '2024-08-13'),
(75, 5, 18, 3, 'Chocolate Cake was too sweet.', '2024-08-14'),
(76, 6, 18, 5, 'Chocolate Cake was rich and moist.', '2024-08-15'),
(77, 9, 20, 3, 'Fruit Salad was okay, not very fresh.', '2024-08-18'),
(78, 10, 20, 4, 'Fruit Salad was fresh and refreshing.', '2024-08-19');



CREATE TABLE IF NOT EXISTS todayMenu (
    menuItemId BIGINT UNSIGNED NOT NULL,
    PRIMARY KEY (menuItemId),
    FOREIGN KEY (menuItemId) REFERENCES MenuItem(menuItemId)
);


ALTER TABLE Feedback
DROP FOREIGN KEY Feedback_ibfk_2;

ALTER TABLE Feedback
ADD CONSTRAINT Feedback_ibfk_2
FOREIGN KEY (MenuItemId) REFERENCES MenuItem(menuItemId)
ON DELETE CASCADE;

CREATE TABLE Notification (
    notificationId INT AUTO_INCREMENT PRIMARY KEY,
    notificationTitle VARCHAR(255) NOT NULL,
    message TEXT NOT NULL,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);


INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, Availability, Price) VALUES
(19, 'Spicy Chicken Wings', 3, true, 11.49),       -- Dinner (non-veg)


-- Insert bad ratings with comments
INSERT INTO Feedback (feedbackId, userId, MenuItemId, Rating, comment, timestamp) VALUES
(80, 3, 1, 1, 'Masala Dosa was burnt and inedible.', '2024-08-16'),
(81, 4, 5, 1, 'Chicken Biryani was extremely dry and overcooked.', '2024-08-17'),
(82, 6, 7, 1, 'Butter Chicken had a weird aftertaste and was too oily.', '2024-08-18'),
(83, 7, 9, 1, 'Idli Sambar was cold and lacked flavor.', '2024-08-19'),
(84, 8, 11, 1, 'Egg Benedict was undercooked and the sauce was bland.', '2024-08-20'),
(85, 9, 13, 1, 'Pulao was undercooked and tasteless.', '2024-08-21'),
(86, 10, 15, 1, 'Fish Tacos were soggy and the fish was not fresh.', '2024-08-22'),
(87, 1, 17, 1, 'Vegetable Biryani was mushy and had no taste.', '2024-08-23'),
(88, 2, 18, 1, 'Chocolate Cake was dry and not sweet enough.', '2024-08-24'),
(90, 4, 20, 1, 'Fruit Salad was old and not fresh at all.', '2024-08-26');

-- Create the discardMenuItemDetailedFeedback table
CREATE TABLE discardMenuItemDetailedFeedback (
    id INT AUTO_INCREMENT PRIMARY KEY,
    userId BIGINT UNSIGNED,
    menuItemId BIGINT UNSIGNED,
    whatYouLiked VARCHAR(255),
    howWouldItTaste VARCHAR(255),
    shareRecipe VARCHAR(255),
    FOREIGN KEY (userId) REFERENCES User(userId) ON DELETE CASCADE,
    FOREIGN KEY (menuItemId) REFERENCES MenuItem(menuItemId) ON DELETE CASCADE
);

-- Create the UserProfile table
CREATE TABLE UserProfile (
    userId BIGINT UNSIGNED PRIMARY KEY,
    vegetarianPreference INT,
    spiceLevelOption INT,
    cuisinePreference INT,
    sweetToothPreference INT,
    FOREIGN KEY (userId) REFERENCES User(userId) ON DELETE CASCADE
);

-- Clear the existing data from MenuItem table
DELETE FROM MenuItem;

-- Adding columns to MenuItem table
ALTER TABLE MenuItem
ADD COLUMN vegetarianPreference INT,
ADD COLUMN spiceLevelOption INT,
ADD COLUMN cuisinePreference INT,
ADD COLUMN sweetToothPreference INT;

-- Inserting new menu items with updated columns
INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, Availability, Price, vegetarianPreference, spiceLevelOption, cuisinePreference, sweetToothPreference) VALUES
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


INSERT INTO UserProfile (userId, vegetarianPreference, spiceLevelOption, cuisinePreference, sweetToothPreference) VALUES
(1, 1, 1, 1, 1), -- john_doe
(2, 2, 2, 2, 0), -- jane_smith
(3, 3, 3, 3, 1), -- chef_ravi
(4, 1, 1, 1, 1), -- employee_mike
(5, 2, 2, 2, 0), -- employee_susan
(6, 3, 3, 3, 1), -- admin_anna
(7, 1, 1, 1, 1), -- chef_kumar
(8, 2, 2, 2, 0), -- employee_johnny
(9, 3, 3, 3, 1), -- admin_sam
(10, 1, 1, 1, 1), -- chef_alia
(11, 2, 2, 2, 0), -- vanshaj
(12, 3, 3, 3, 1), -- DadhichV
(13, 1, 1, 1, 1); -- InTimeTec


-- Insert new items into MenuItem table
INSERT INTO MenuItem (menuItemId, menuItemName, menuItemType, availability, price, vegetarianPreference, spiceLevelOption, cuisinePreference, sweetToothPreference) VALUES
(21, 'Mixed Vegetable Curry', 2, true, 130, 1, 2, 1, 0),
(22, 'Fish Fry', 2, true, 180, 2, 1, 2, 0),
(23, 'Mushroom Soup', 3, true, 100, 1, 3, 3, 0),
(24, 'Pasta Alfredo', 2, true, 160, 1, 1, 3, 0),
(25, 'Apple Pie', 4, true, 70, 1, 3, 3, 1);

-- Insert bad feedback into Feedback table
INSERT INTO Feedback (feedbackId, userId, menuItemId, rating, comment, timestamp) VALUES
(81, 1, 21, 1, 'The curry was too watery and bland.', '2024-07-04'),
(82, 2, 21, 1, 'Vegetables were not cooked properly.', '2024-07-04'),
(83, 3, 22, 1, 'The fish was overcooked and dry.', '2024-07-04'),
(84, 4, 22, 1, 'Too salty and greasy.', '2024-07-04'),
(85, 5, 23, 1, 'Mushroom soup was too watery and tasteless.', '2024-07-04'),
(86, 6, 23, 1, 'No flavor and too much cream.', '2024-07-04'),
(87, 7, 24, 1, 'Pasta was undercooked and sauce was bland.', '2024-07-04'),
(88, 8, 24, 1, 'Terrible taste, not worth the price.', '2024-07-04'),
(89, 9, 25, 1, 'Apple pie crust was too hard and filling was bland.', '2024-07-04'),
(90, 10, 25, 1, 'Worst dessert I have ever tasted.', '2024-07-04');


CREATE EVENT delete_old_notifications
ON SCHEDULE EVERY 1 DAY
STARTS CURRENT_TIMESTAMP
DO
  DELETE FROM Notification
  WHERE date < CURDATE();


ALTER TABLE UserProfile
CHANGE COLUMN foodPreference cuisinePreference INT;


CREATE EVENT delete_today_menu_entries
ON SCHEDULE EVERY 1 DAY
STARTS TIMESTAMP(CURRENT_DATE + INTERVAL 1 DAY)
DO
  DELETE FROM todayMenu;
