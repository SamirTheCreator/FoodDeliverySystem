#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handlers.h"

extern struct foodle_event_t event;
extern union foodle_data_u data;

int mealID = 0;

struct fooodle_handler_t* initChainedHandler()
{
	struct fooodle_handler_t *chain = (struct fooodle_handler_t *)malloc(sizeof(struct fooodle_handler_t));
	if (chain == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		return NULL;
	}
	chain->type = -1;
	chain->next = NULL;
	
	addHandler(chain, AUTHENTICATE_ACCOUNT, authenticateAccount);
	addHandler(chain, GET_ACCOUNT, getAccount);
	addHandler(chain, UPDATE_ACCOUNT, updateAccount);
	addHandler(chain, DELETE_ACCOUNT, deleteAccount);
	
	addHandler(chain, GET_ORDER_LIST, getOrderList);
	addHandler(chain, SELECT_ORDER, selectOrder);
	addHandler(chain, FINISH_ORDER, finishOrder);
	
	addHandler(chain, GET_MENU, getMenu);
	addHandler(chain, ADD_MEAL, addMeal);
	addHandler(chain, UPDATE_MEAL, updateMeal);
	addHandler(chain, DELETE_MEAL, deleteMeal);
	
	addHandler(chain, GET_RESTAURANT_LIST, getRestaurantList);
	addHandler(chain, VIEW_CART, viewCart);
	addHandler(chain, ADD_ITEM, addItem);
	addHandler(chain, UPDATE_ITEM, updateItem);
	addHandler(chain, DELETE_ITEM, deleteItem);
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

void handleEvent(struct fooodle_handler_t *chain, struct foodle_event_t *event)
{
	struct fooodle_handler_t *current_handler = chain;
	while (current_handler) {
		if (current_handler->type == event->type) {
			current_handler->handler(event);
			break;
		}

		current_handler = current_handler->next;
	}
}

//handlers are mainly intended for requesting certain function from dbconnector
//and parse retreived table or json file to union data
int authenticateAccount(struct foodle_event_t *event)
{
	printf("Handling event type AUTHENTICATE_ACCOUNT\n");
	
	if (strcmp(event->data.account.name, "mukhabbat") || strcmp(event->data.account.password, "12345678"))
		return 0;
		
	data.account.clientID = 1;
	
	return 1;
}

int getAccount(struct foodle_event_t *event)
{
	printf("Handling event GET_ACCOUNT\n");
	
	strcpy(data.account.email, "sample@mail.com");
	strcpy(data.account.password, event->data.account.password);
	data.account.type = Customer;
	
	strcpy(data.account.name, event->data.account.name);
	strcpy(data.account.phone, "+998901234567");
	strcpy(data.account.address, "Uzbekistan");
	
	return 1;
}

int updateAccount(struct foodle_event_t *event)
{
	printf("Handling event UPDATE_ACCOUNT\n");
	
	strcpy(data.account.email, "sample@mail.com");
	strcpy(data.account.password, event->data.account.password);
	data.account.type = Customer;
	
	strcpy(data.account.name, event->data.account.name);
	strcpy(data.account.phone, "+998901234567");
	strcpy(data.account.address, "Uzbekistan");

	return 1;
}

int deleteAccount(struct foodle_event_t *event) { printf("Handling event DELETE_ACCOUNT\n"); }

int getOrderList(struct foodle_event_t *event)
{
	printf("Handling event GET_ORDER_LIST\n");
	data.order_list[0] = (struct foodle_order_t){};
}

int selectOrder(struct foodle_event_t *event)
{
	printf("Handling event SELECT_ORDER\n");
	data.order.restaurantID = 1;
	data.order.status = Preparing;
}

int finishOrder(struct foodle_event_t *event)
{
	printf("Handling event FINISH_ORDER\n");
	data.order.status = Finished;
}

int getMenu(struct foodle_event_t *event)
{
	printf("Handling event GET_MENU\n");
	data.menu.restaurantID = 1;
}

int addMeal(struct foodle_event_t *event)
{
	printf("Handling event ADD_MEAL\n");
	data.meal.mealID = mealID++;
}

int updateMeal(struct foodle_event_t *event)
{
	printf("Handling event UPDATE_MEAL\n");
	data.meal.mealID = mealID;
}

int deleteMeal(struct foodle_event_t *event)
{
	printf("Handling event DELETE_MEAL\n");
	data.meal.mealID = mealID--;
}

int getRestaurantList(struct foodle_event_t *event) { printf("Handling event GET_RESTAURANTS_LIST\n"); }
int viewCart(struct foodle_event_t *event) { printf("Handling event VIEW_CART\n"); }
int addItem(struct foodle_event_t *event) { printf("Handling event ADD_ITEM\n"); }
int updateItem(struct foodle_event_t *event) { printf("Handling event UPDATE_ITEM\n"); }
int deleteItem(struct foodle_event_t *event) { printf("Handling event DELETE_ITEM\n"); }
int orderCart(struct foodle_event_t *event) { printf("Handling event ORDER_CART\n"); }

int getDeliveryList(struct foodle_event_t *event) { printf("Handling event GET_DELIVERY_LIST\n"); }
int chooseDelivery(struct foodle_event_t *event) { printf("Handling event CHOOSE_DELIVERY\n"); }
int withdrawDelivery(struct foodle_event_t *event) { printf("Handling event WITHDRAW_DELIVERY\n"); }
int finishDelivery(struct foodle_event_t *event) { printf("Handling event FINISH_DELIVERY\n"); }

