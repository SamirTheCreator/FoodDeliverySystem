-- customer Table
CREATE TABLE `customer` (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    phone_number VARCHAR(20) UNIQUE,
    password VARCHAR(255), -- Stored as a hash
    address VARCHAR(255),
    -- email VARCHAR(255)
);

-- Restaurant Table
CREATE TABLE restaurant (
    restaurant_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    password VARCHAR(255),
    phone_number VARCHAR(20),
    address VARCHAR(255),
);

-- -- Category Table
-- CREATE TABLE category (
--     category_id INT AUTO_INCREMENT PRIMARY KEY,
--     name VARCHAR(255)
-- );

-- Dasher (Delivery Person) Table
CREATE TABLE dasher (
    dasher_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    delivery_type VARCHAR(50),
    phone_number VARCHAR(20),
    -- rating FLOAT
);

-- Menu Table
CREATE TABLE menu (
    menu_id INT AUTO_INCREMENT PRIMARY KEY,
    restaurant_id INT,
    FOREIGN KEY (restaurant_id) REFERENCES restaurant(restaurant_id) ON DELETE CASCADE
);

-- Meal Table
CREATE TABLE meal (
    meal_id INT AUTO_INCREMENT PRIMARY KEY,
    menu_id INT,
    name VARCHAR(255),
    price DECIMAL(10,2),
    image_path VARCHAR(255),
    category_id VARCHAR(255),
    FOREIGN KEY (menu_id) REFERENCES menu(menu_id) ON DELETE CASCADE,
    FOREIGN KEY (category_id) REFERENCES category(category_id) ON DELETE SET NULL
);

-- Order Table
CREATE TABLE `order` (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    restaurant_id INT,
    address TEXT,
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
    meal_id INT,
    quantity INT,
    FOREIGN KEY (order_id) REFERENCES `order`(order_id) ON DELETE CASCADE,
    FOREIGN KEY (meal_id) REFERENCES meal(meal_id) ON DELETE CASCADE,
    PRIMARY KEY (order_id, meal_id)
);