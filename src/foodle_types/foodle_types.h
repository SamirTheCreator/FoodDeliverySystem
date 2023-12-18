#ifndef FOODLE_TYPES_H
#define FOODLE_TYPES_H

#define str(x) #x
#define MAXSIZE 255

typedef char string[MAXSIZE];

enum foodle_user_type_e {
	Restaurant,
	Customer,
	Dasher
};

struct foodle_user_t {
	int ID;
	string name;
	string password;
	enum foodle_user_type_e type;
	string email;
	string phone;
	string address;
	string region;
	string image_path;
	string delivery_type;
};

struct foodle_meal_t {
	int ID;
	string name;
	float price;
	string image_path;
};

struct foodle_menu_t {
	struct foodle_meal_t meal[MAXSIZE];
};

struct foodle_restaurant_t {
	int ID;
	string name;
	struct foodle_menu_t menu;
	string address;
};

struct foodle_item_t {
	int meal_id;
	int quantity;
	float net_price;
};

struct foodle_cart_t {
	struct foodle_item_t item[MAXSIZE];
	int total_price;
};

struct foodle_delivery_t {
	int orderID;
	string restaurant_address;
	string customer_address;
};

enum foodle_order_status_e {
	Pending,
	Confirmed,
	Preparing,
	Delivering,
	Finished
};

struct foodle_order_t {
	int ID;
	int customerID;
	int restaurantID;
	int dasherID;
	string status;
	string address;
	string date;
	struct foodle_cart_t cart;
};

union foodle_data_u {
	struct foodle_user_t user;
	struct foodle_menu_t menu;
	struct foodle_meal_t meal;
	struct foodle_restaurant_t restaurant;
	struct foodle_restaurant_t restaurant_list[MAXSIZE];
	struct foodle_order_t order;
	struct foodle_order_t order_list[MAXSIZE];
	struct foodle_delivery_t delivery;
	struct foodle_delivery_t delivery_list[MAXSIZE];
};

enum foodle_event_type_e {
	AUTHENTICATE_USER,
	GET_USER_INFO,
	UPDATE_USER_INFO,
	DELETE_USER_INFO,

	ADD_MEAL,
	GET_MEAL,
	UPDATE_MEAL,
	DELETE_MEAL,

	GET_RESTAURANT_LIST,
	GET_MENU,
	ORDER_CART,
	
	GET_ORDER_LIST,
	SELECT_ORDER,
	FINISH_ORDER,

	GET_DELIVERY_LIST,
	CHOOSE_DELIVERY,
	WITHDRAW_DELIVERY,
	FINISH_DELIVERY
};

struct foodle_event_t {
	enum foodle_event_type_e type;
	union foodle_data_u data;
};

#endif // FOODLE_TYPES_H
