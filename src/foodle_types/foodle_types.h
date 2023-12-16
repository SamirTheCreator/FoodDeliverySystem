#ifndef FOODLE_CLIENT_TYPES_H__
#define FOODLE_CLIENT_TYPES_H__

#define MAXSIZE 16

typedef char string[MAXSIZE];

enum foodle_account_type_e {
	Restaurant,
	Customer,
	Dasher
};

struct foodle_account_t {
	int clientID;
	string email;
	string password;
	enum foodle_account_type_e type;
	string name;
	string phone;
	string address;
	string car_info;
};

struct foodle_meal_t {
	int mealID;
	string name;
	float price;
};

struct foodle_menu_t {
	int restaurantID;
	string restaurant_name;
	struct foodle_meal_t meal[MAXSIZE];
};

struct foodle_item_t {
	struct foodle_meal_t meal;
	int quantity;
	float net_price;
};

struct foodle_cart_t {
	int cartID;
	struct foodle_item_t item[MAXSIZE];
	int total_price;
};

struct foodle_restaurant_t {
	int restaurantID;
	char name[MAXSIZE];
	char category[MAXSIZE];
	char address[MAXSIZE];
};

struct foodle_delivery_t {
	int orderID;
	string name;
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
	int orderID;
	int customerID;
	int restaurantID;
	int dasherID;
	enum foodle_order_status_e status;
	string address;
	time_t avg_preparation_time;
	time_t avg_delivery_time;
	time_t avg_arrival_time;
	struct foodle_cart_t cart;
};

union foodle_data_u {
	struct foodle_account_t account;
	struct foodle_menu_t menu;
	struct foodle_meal_t meal;
	struct foodle_restaurant_t restaurant;
	struct foodle_restaurant_t restaurant_list[MAXSIZE];
	struct foodle_cart_t cart;
	struct foodle_item_t item;
	struct foodle_order_t order;
	struct foodle_order_t order_list[MAXSIZE];
	struct foodle_delivery_t delivery;
	struct foodle_delivery_t delivery_list[MAXSIZE];
};

enum foodle_event_type_e {
	AUTHENTICATE_ACCOUNT,
	GET_ACCOUNT,
	UPDATE_ACCOUNT,
	DELETE_ACCOUNT,

	GET_ORDER_LIST,
	SELECT_ORDER,
	FINISH_ORDER,

	GET_MENU,
	ADD_MEAL,
	UPDATE_MEAL,
	DELETE_MEAL,

	GET_RESTAURANT_LIST,
	VIEW_CART,
	ADD_ITEM,
	UPDATE_ITEM,
	DELETE_ITEM,
	ORDER_CART,

	GET_DELIVERY_LIST,
	CHOOSE_DELIVERY,
	WITHDRAW_DELIVERY,
	FINISH_DELIVERY
};

struct foodle_event_t {
	enum foodle_event_type_e type;
	union foodle_data_u data;
};

#endif // FOODLE_CLIENT_TYPES_H__
