#ifndef FOODLE_TYPES_H__
#define FOODLE_TYPES_H__

#define MAXSIZE 255

enum foodle_account_type_e {
	Restaurant,
	Customer,
	Dasher
};

struct foodle_account_t {
	int clientID;
	char email[MAXSIZE];
	char password[MAXSIZE];
	enum foodle_account_type_e type;
	char name[MAXSIZE];
	char phone[MAXSIZE];
	char address[MAXSIZE];
	char car_info[MAXSIZE];
};

struct foodle_item_t {
	int itemID;
	char name[MAXSIZE];
	int quantity;
	float price;
};

struct foodle_cart_t {
	int cartID;
	struct foodle_item_t item[MAXSIZE];
	int total_price;
};

struct foodle_meal_t {
	int mealID;
	char name[MAXSIZE];
	float price;
};

struct foodle_menu_t {
	int restaurantID;
	char restaurant_name[MAXSIZE];
	struct foodle_meal_t meal[MAXSIZE];
};


struct foodle_restaurant_t {
	int restaurantID;
	char name[MAXSIZE];
	char category[MAXSIZE];
	char address[MAXSIZE];
};

struct foodle_delivery_t {
	int orderID;
	char name[MAXSIZE];
	char restaurant_address[MAXSIZE];
	char customer_address[MAXSIZE];
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
	char address[MAXSIZE];
	time_t avg_preparation_time;
	time_t avg_delivery_time;
	time_t avg_arrival_time;
	struct foodle_cart_t cart;
};

union foodle_data_u {
	struct foodle_account_t account;
	struct foodle_cart_t cart;
	struct foodle_item_t item;
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

#endif FOODLE_TYPES_H__ // FOODLE_TYPES_H__