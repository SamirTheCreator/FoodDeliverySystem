START TRANSACTION;

DROP TABLE IF EXISTS order_meal;
DROP TABLE IF EXISTS `order`;
DROP TABLE IF EXISTS menu;
DROP TABLE IF EXISTS `user`;
-- User Table
CREATE TABLE `user` (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    phone_number VARCHAR(20) UNIQUE,
    email VARCHAR(255) UNIQUE,
    password VARCHAR(255),
    address VARCHAR(255),       -- For customers and restaurants
    user_type ENUM('Customer', 'Restaurant', 'Dasher'),
    -- Additional attributes for Restaurant
    region VARCHAR(255),        -- Nullable, only for restaurants
    image_path VARCHAR(255),    -- Nullable, only for restaurants
    -- Additional attributes for Dasher
    delivery_type VARCHAR(50)   -- Nullable, only for dashers
);

-- Menu Table (remains the same)
CREATE TABLE menu (
    menu_id INT AUTO_INCREMENT PRIMARY KEY,
    restaurant_id INT,
    item_name VARCHAR(255),
    item_price DECIMAL(10,2),
    item_image_path VARCHAR(255),
    FOREIGN KEY (restaurant_id) REFERENCES user(user_id) ON DELETE CASCADE,
    UNIQUE (restaurant_id, item_name, item_price)
);

-- Order Table
CREATE TABLE `order` (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    restaurant_id INT,
    dasher_id INT,
    date DATETIME,
    order_status ENUM('Placed', 'Preparing', 'Ready for delivery', 'Out for delivery', 'Delivered') DEFAULT 'Placed',
    FOREIGN KEY (customer_id) REFERENCES user(user_id) ON DELETE SET NULL,
    FOREIGN KEY (restaurant_id) REFERENCES user(user_id) ON DELETE SET NULL,
    FOREIGN KEY (dasher_id) REFERENCES user(user_id) ON DELETE SET NULL
);

-- Order-Meal Junction Table (remains the same)
CREATE TABLE order_meal (
    order_id INT,
    menu_id INT,
    quantity INT DEFAULT 1,
    FOREIGN KEY (order_id) REFERENCES `order`(order_id) ON DELETE CASCADE,
    FOREIGN KEY (menu_id) REFERENCES menu(menu_id) ON DELETE CASCADE,
    PRIMARY KEY (order_id, menu_id)
);
COMMIT;
