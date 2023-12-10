START TRANSACTION;

DROP TABLE IF EXISTS order_meal;
DROP TABLE IF EXISTS `order`;
DROP TABLE IF EXISTS menu;
DROP TABLE IF EXISTS dasher;
DROP TABLE IF EXISTS restaurant;
DROP TABLE IF EXISTS `customer`;

-- Customer Table
CREATE TABLE `customer` (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    phone_number VARCHAR(20) UNIQUE,
    email VARCHAR(255) UNIQUE,
    password VARCHAR(255), -- Stored as a hash
    address VARCHAR(255)
);

-- Restaurant Table
CREATE TABLE restaurant (
    restaurant_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    phone_number VARCHAR(20),
    address VARCHAR(255),
    region VARCHAR(255),
    image_path VARCHAR(255)
);


-- Dasher (Delivery Person) Table
CREATE TABLE dasher (
    dasher_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    delivery_type VARCHAR(50),
    phone_number VARCHAR(20)
);

-- Menu Table
CREATE TABLE menu (
    menu_id INT AUTO_INCREMENT PRIMARY KEY,
    restaurant_id INT,
    item_name VARCHAR(255),
    item_price DECIMAL(10,2),
    item_image_path VARCHAR(255),
    FOREIGN KEY (restaurant_id) REFERENCES restaurant(restaurant_id) ON DELETE CASCADE,
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
    FOREIGN KEY (customer_id) REFERENCES `customer`(customer_id) ON DELETE SET NULL,
    FOREIGN KEY (restaurant_id) REFERENCES restaurant(restaurant_id) ON DELETE SET NULL,
    FOREIGN KEY (dasher_id) REFERENCES dasher(dasher_id) ON DELETE SET NULL
);

-- Order-Meal Junction Table
CREATE TABLE order_meal (
    order_id INT,
    menu_id INT,
    FOREIGN KEY (order_id) REFERENCES `order`(order_id) ON DELETE CASCADE,
    FOREIGN KEY (menu_id) REFERENCES menu(menu_id) ON DELETE CASCADE,
    PRIMARY KEY (order_id, menu_id)
);
COMMIT;