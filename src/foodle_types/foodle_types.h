#ifndef FOODLE_TYPES_H__
#define FOODLE_TYPES_H__

#define MAXSIZE 255

enum account_type {
	Restaurant,
	Customer,
	Dasher
};

struct Account {
	int clientID;
	char email[MAXSIZE];
	char password[MAXSIZE];
	enum account_type type;
	char name[MAXSIZE];
	char phone[MAXSIZE];
	char address[MAXSIZE];
	char car_info[MAXSIZE];
};

struct Item {
	int itemID;
	char name[MAXSIZE];
	int quantity;
	float price;
};

struct Cart {
	int cartID;
	struct Item item[MAXSIZE];
	int total_price;
};

struct Meal {
	int mealID;
	char name[MAXSIZE];
	float price;
};

struct Menu {
	int restaurantID;
	char restaurant_name[MAXSIZE];
	struct Meal meal[MAXSIZE];
};


struct Restaurant {
	int restaurantID;
	char name[MAXSIZE];
	char category[MAXSIZE];
	char address[MAXSIZE];
};

struct Delivery {
	int orderID;
	char name[MAXSIZE];
	char restaurant_address[MAXSIZE];
	char customer_address[MAXSIZE];
};

enum order_status {
	Pending,
	Confirmed,
	Preparing,
	Delivering,
	Finished
};

struct Order {
	int orderID;
	int customerID;
	int restaurantID;
	int dasherID;
	enum order_status status;
	char address[MAXSIZE];
	time_t avg_preparation_time;
	time_t avg_delivery_time;
	time_t avg_arrival_time;
	struct Cart cart;
};

union Data {
	struct Account account;
	struct Cart cart;
	struct Item item;
	struct Menu menu;
	struct Meal meal;
	struct Restaurant restaurant;
	struct Restaurant restaurant_list[MAXSIZE];
	struct Order order;
	struct Order order_list[MAXSIZE];
	struct Delivery delivery;
	struct Delivery delivery_list[MAXSIZE];
};

enum event_type {
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

struct Event {
	enum event_type type;
	union Data data;
};

typedef enum event_type 	foodle_event_type_e;
typedef struct Event 		foodle_event_t;
typedef union Data 			foodle_data_u;
typedef enum account_type 	foodle_account_type_e;
typedef struct Account 		foodle_account_t;
typedef struct Cart 		foodle_cart_t;
typedef struct Item 		foodle_item_t;
typedef struct Menu 		foodle_menu_t;
typedef struct Meal 		foodle_meal_t;
typedef struct Restaurant 	foodle_restaurant_t;
typedef struct Delivery 	foodle_delivery_t;
typedef enum order_status 	foodle_order_status_e;
typedef struct Order 		foodle_order_t;

#endif FOODLE_TYPES_H__ // FOODLE_TYPES_H__
