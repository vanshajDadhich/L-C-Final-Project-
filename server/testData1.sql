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

-- Insert additional Feedback entries
INSERT INTO Feedback (feedbackId, userId, MenuItemId, Rating, comment, timestamp) VALUES
(11, 1, 11, 4, 'Eggs were cooked perfectly, but could use more seasoning.', '2024-06-11'),
(12, 2, 21, 5, 'Fluffy pancakes with a great maple syrup!', '2024-06-12'),
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
(30, 10, 21, 5, 'Best pancakes ever, fluffy and delicious!', '2024-06-30'),
(31, 1, 11, 5, 'Egg Benedict was amazing, loved the hollandaise sauce!', '2024-07-01'),
(32, 2, 21, 4, 'Pancakes were good, could be a bit crispier.', '2024-07-02'),
(33, 3, 13, 3, 'Pulao lacked seasoning, needs improvement.', '2024-07-03'),
(34, 4, 14, 4, 'Chicken curry was flavorful, but a bit too spicy.', '2024-07-04'),
(35, 5, 15, 5, 'Fish Tacos were superb, fresh and tasty.', '2024-07-05'),
(36, 6, 16, 4, 'Steak was good, could have been more tender.', '2024-07-06'),
(37, 7, 17, 3, 'Vegetable biryani was okay, could use more vegetables.', '2024-07-07'),
(38, 8, 18, 5, 'Chocolate cake was heavenly, loved every bite!', '2024-07-08'),
(39, 9, 19, 4, 'Spicy chicken wings were delicious, perfect level of spice.', '2024-07-09'),
(40, 10, 20, 5, 'Refreshing fruit salad, perfect for a summer day.', '2024-07-10');