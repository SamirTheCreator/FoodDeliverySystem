START TRANSACTION;


INSERT INTO customer (name, phone_number, email, password, address) VALUES
('John Doe', '1234567890', 'johndoe@example.com', 'hashed_password_1', '1234 Main St'),
('Jane Smith', '2345678901', 'janesmith@example.com', 'hashed_password_2', '5678 Market Ave'),
('Alice Johnson', '3456789012', 'alicejohnson@example.com', 'hashed_password_3', '9101 College Blvd'),
('Emily Turner', '4567890123', 'emilyturner@example.com', 'hashed_password_4', '2022 Willow Park'),
('Michael Brown', '5678901234', 'michaelbrown@example.com', 'hashed_password_5', '3048 Maple Ave'),
('Isabella Clark', '6789012345', 'isabellaclark@example.com', 'hashed_password_6', '4556 Oak Street'),
('Ethan Davis', '7890123456', 'ethandavis@example.com', 'hashed_password_7', '902 South Street'),
('Sophia Martinez', '8901234567', 'sophiamartinez@example.com', 'hashed_password_8', '1122 Elm Road'),
('James Wilson', '9012345678', 'jameswilson@example.com', 'hashed_password_9', '634 Pine Lane'),
('Olivia Taylor', '0123456789', 'oliviataylor@example.com', 'hashed_password_10', '781 Cedar Blvd');


INSERT INTO restaurant (name, phone_number, address, region, image_path) VALUES
('Tasty Treats', '9876543210', '100 Food Lane', 'North', '/images/tasty_treats.jpg'),
('Pizza Palace', '8765432109', '200 Pizza Court', 'East', '/images/pizza_palace.jpg'),
('Burger Bonanza', '7654321098', '300 Burger Blvd', 'South', '/images/burger_bonanza.jpg'),
('Taco Town', '6543210987', '400 Taco Trail', 'West', '/images/taco_town.jpg'),
('Sushi Spot', '5432109876', '500 Sushi Street', 'North', '/images/sushi_spot.jpg'),
('Pasta Place', '4321098765', '600 Pasta Parkway', 'East', '/images/pasta_place.jpg'),
('Chicken Shack', '3210987654', '700 Chicken Circle', 'South', '/images/chicken_shack.jpg'),
('Salad Stop', '2109876543', '800 Salad Street', 'West', '/images/salad_stop.jpg'),
('Sandwich Shop', '1098765432', '900 Sandwich Square', 'North', '/images/sandwich_shop.jpg'),
('Dessert Delights', '0987654321', '1000 Dessert Drive', 'East', '/images/dessert_delights.jpg');


INSERT INTO dasher (name, delivery_type, phone_number) VALUES
('David Runner', 'Bike', '4445556666'),
('Emma Speed', 'Car', '5556667777'),
('Lucas Quick', 'Scooter', '6667778888'),
('Ava Fast', 'Bike', '7778889999'),
('Mia Swift', 'Car', '8889990000'),
('Noah Rapid', 'Scooter', '9990001111'),
('Oliver Hasty', 'Bike', '0001112222'),
('Sophia Rapid', 'Car', '1112223333'),
('William Speedy', 'Scooter', '2223334444'),
('Isabella Swift', 'Bike', '3334445555');




INSERT INTO menu (restaurant_id, item_name, item_price, item_image_path) VALUES
(1, 'Cheese Pizza', 9.99, '/menu/cheese_pizza.jpg'),
(1, 'Pepperoni Pizza', 10.99, '/menu/pepperoni_pizza.jpg'),
(2, 'Classic Burger', 8.99, '/menu/classic_burger.jpg'),
(2, 'Cheeseburger', 9.99, '/menu/cheeseburger.jpg'),
(3, 'Chicken Taco', 7.99, '/menu/chicken_taco.jpg'),
(3, 'Beef Taco', 8.99, '/menu/beef_taco.jpg'),
(4, 'California Roll', 9.99, '/menu/california_roll.jpg'),
(4, 'Spicy Tuna Roll', 10.99, '/menu/spicy_tuna_roll.jpg'),
(5, 'Spaghetti', 8.99, '/menu/spaghetti.jpg'),
(5, 'Fettuccine Alfredo', 9.99, '/menu/fettuccine_alfredo.jpg'),
(6, 'Chicken Parmesan', 10.99, '/menu/chicken_parmesan.jpg'),
(6, 'Lasagna', 11.99, '/menu/lasagna.jpg'),
(7, 'Chicken Sandwich', 8.99, '/menu/chicken_sandwich.jpg'),
(7, 'Turkey Sandwich', 9.99, '/menu/turkey_sandwich.jpg'),
(8, 'Caesar Salad', 7.99, '/menu/caesar_salad.jpg'),
(8, 'Cobb Salad', 8.99, '/menu/cobb_salad.jpg'),
(9, 'Chocolate Chip Cookie', 2.99, '/menu/chocolate_chip_cookie.jpg'),
(9, 'Brownie', 3.99, '/menu/brownie.jpg'),
(10, 'Ice Cream', 4.99, '/menu/ice_cream.jpg'),
(10, 'Cake', 5.99, '/menu/cake.jpg');



INSERT INTO `order` (customer_id, restaurant_id, dasher_id, date, order_status) VALUES
(1, 1, 1, '2023-01-01 12:00:00', 'Delivered'),
(2, 2, 2, '2023-01-02 13:00:00', 'Out for delivery'),
(3, 3, 3, '2023-01-03 14:00:00', 'Preparing'),
(4, 4, 4, '2023-01-04 15:00:00', 'Ready for delivery'),
(5, 5, 5, '2023-01-05 16:00:00', 'Placed'),
(6, 6, 6, '2023-01-06 17:00:00', 'Placed'),
(7, 7, 7, '2023-01-07 18:00:00', 'Placed'),
(8, 8, 8, '2023-01-08 19:00:00', 'Placed'),
(9, 9, 9, '2023-01-09 20:00:00', 'Placed'),
(10, 10, 10, '2023-01-10 21:00:00', 'Placed');



INSERT INTO order_meal (order_id, menu_id) VALUES
(1, 1),
(1, 2),
(2, 3),
(2, 4),
(3, 5),
(3, 6),
(4, 7),
(4, 8),
(5, 9),
(5, 10),
(6, 11),
(6, 12),
(7, 13),
(7, 14),
(8, 15),
(8, 16),
(9, 17),
(9, 18),
(10, 19),
(10, 20);
COMMIT;