#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "handlers.h"

extern struct foodle_event_t event;
extern union foodle_data_u data;

//Database on server
char *names[] = { "restaurant", "customer", "dasher" };
struct foodle_menu_t menu = { .restaurantID = 0, .restaurant_name = "Restaurant"};
struct foodle_user_t user[10];
static int mealID;
static int userID;

struct fooodle_handler_t* initChainedHandler()
{
	struct fooodle_handler_t *chain = (struct fooodle_handler_t *)malloc(sizeof(struct fooodle_handler_t));
	if (chain == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		return NULL;
	}
	chain->type = -1;
	chain->next = NULL;
	
	addHandler(chain, AUTHENTICATE_USER, authenticateUser);
	addHandler(chain, GET_USER_INFO, getUserInfo);
	addHandler(chain, UPDATE_USER_INFO, updateUserInfo);
	addHandler(chain, DELETE_USER_INFO, deleteUserInfo);
	
	addHandler(chain, ADD_MEAL, addMeal);
	addHandler(chain, UPDATE_MEAL, updateMeal);
	addHandler(chain, DELETE_MEAL, deleteMeal);
	
	addHandler(chain, GET_ORDER_LIST, getOrderList);
	addHandler(chain, SELECT_ORDER, selectOrder);
	addHandler(chain, FINISH_ORDER, finishOrder);
	
	addHandler(chain, GET_RESTAURANT_LIST, getRestaurantList);
	addHandler(chain, GET_MENU, getMenu);
	addHandler(chain, ORDER_CART, orderCart);
	
	addHandler(chain, GET_DELIVERY_LIST, getDeliveryList);
	addHandler(chain, CHOOSE_DELIVERY, chooseDelivery);
	addHandler(chain, WITHDRAW_DELIVERY, withdrawDelivery);
	addHandler(chain, FINISH_DELIVERY, finishDelivery);
	
	return chain;
}

void addHandler(struct fooodle_handler_t *chain, enum foodle_event_type_e type, int (*handler)())
{
	struct fooodle_handler_t *current_handler = chain;
	while (current_handler->next)
		current_handler = current_handler->next;
		
	struct fooodle_handler_t *new_handler = (struct fooodle_handler_t *)malloc(sizeof(struct fooodle_handler_t));
	new_handler->type = type;
	new_handler->handler = handler;
	new_handler->next = NULL;
	current_handler->next = new_handler;
}

int handleEvent(struct fooodle_handler_t *chain, struct foodle_event_t *event)
{	
	struct fooodle_handler_t *current_handler = chain;
	while (current_handler) {
		if (current_handler->type == event->type)
			return current_handler->handler(event);

		current_handler = current_handler->next;
	}
}

//handlers are mainly intended for requesting certain function from dbconnector
//and parse retreived table or json file to union data
int authenticateUser(struct foodle_event_t *event)
{
	printf("Handling event type AUTHENTICATE_USER\n");
	
	if (strcmp(event->data.user.name, "restaurant")) {
		data.user.userID = -1;
		return 1;
	}
	
	user[userID].userID = userID;
	strcpy(user[userID].name, event->data.user.name);
	strcpy(user[userID].password, event->data.user.password);
	data.user.userID = userID;
	userID++;
	
	return 1;
}

int getUserInfo(struct foodle_event_t *event)
{
	printf("Handling event type GET_USER_INFO\n");

	data.user = user[event->data.user.userID];
	
	return 1;
}

int updateUserInfo(struct foodle_event_t *event)
{
	printf("Handling event type UPDATE_USER_INFO\n");
	
	strcpy(user[event->data.user.userID].email, event->data.user.email);
	strcpy(user[event->data.user.userID].password, event->data.user.password);
	user[event->data.user.userID].type = Restaurant;
	strcpy(user[event->data.user.userID].name, event->data.user.name);
	strcpy(user[event->data.user.userID].phone_number, event->data.user.phone_number);
	strcpy(user[event->data.user.userID].address, event->data.user.address);
	strcpy(user[event->data.user.userID].region, event->data.user.region);
	data.user = user[event->data.user.userID];

	return 1;
}

int deleteUserInfo(struct foodle_event_t *event)
{
	printf("Handling event type DELETE_USER_INFO\n");
	
	strcpy(user[event->data.user.userID].email, "");
	strcpy(user[event->data.user.userID].password, "");
	user[event->data.user.userID].type = -1;
	strcpy(user[event->data.user.userID].name, "");
	strcpy(user[event->data.user.userID].phone_number, "");
	strcpy(user[event->data.user.userID].address, "");
	strcpy(user[event->data.user.userID].region, "");
	data.user = user[userID];
	
	return 1;
}


int addMeal(struct foodle_event_t *event)
{
	printf("Handling event type ADD_MEAL\n");
	
	menu.meal[mealID].mealID = mealID;
	strcpy(menu.meal[mealID].name, event->data.meal.name);
	menu.meal[mealID].price = event->data.meal.price;
	data.meal = menu.meal[mealID];
	mealID++;
	
	return 1;
}

int updateMeal(struct foodle_event_t *event)
{
	printf("Handling event type UPDATE_MEAL\n");
	
	strcpy(menu.meal[event->data.meal.mealID].name, event->data.meal.name);
	menu.meal[event->data.meal.mealID].price = event->data.meal.price;
	data.meal = menu.meal[event->data.meal.mealID];
	
	return 1;
}

int deleteMeal(struct foodle_event_t *event)
{
	printf("Handling event type DELETE_MEAL\n");
	
	menu.meal[event->data.meal.mealID].mealID = -1;
	strcpy(menu.meal[event->data.meal.mealID].name, "");
	menu.meal[event->data.meal.mealID].price = 0;
	data.meal = menu.meal[event->data.meal.mealID];
	mealID--;
	
	return 1;
}

int getOrderList(struct foodle_event_t *event)
{
	printf("Handling event type GET_ORDER_LIST\n");
	data.order_list[0] = (struct foodle_order_t){};
}

int selectOrder(struct foodle_event_t *event)
{
	printf("Handling event type SELECT_ORDER\n");
	data.order.restaurantID = 1;
	data.order.status = Preparing;
}

int finishOrder(struct foodle_event_t *event)
{
	printf("Handling event FINISH_ORDER\n");
	data.order.status = Finished;
}

int getRestaurantList(struct foodle_event_t *event) { printf("Handling event type GET_RESTAURANT_LIST\n"); }
int getMenu(struct foodle_event_t *event)
{
	printf("Handling event type GET_MENU\n");
	data.menu.restaurantID = 1;
}
int orderCart(struct foodle_event_t *event) { printf("Handling event type ORDER_CART\n"); }

int getDeliveryList(struct foodle_event_t *event) { printf("Handling event type GET_DELIVERY_LIST\n"); }
int chooseDelivery(struct foodle_event_t *event) { printf("Handling event type CHOOSE_DELIVERY\n"); }
int withdrawDelivery(struct foodle_event_t *event) { printf("Handling event type WITHDRAW_DELIVERY\n"); }
int finishDelivery(struct foodle_event_t *event) { printf("Handling event type FINISH_DELIVERY\n"); }

