#include <stdio.h>
#include <stdlib.h>
#include "ChainedHandler.h"

struct Handler* initChainedHandler()
{
	struct Handler *chain = (struct Handler *)malloc(sizeof(struct Handler));
	if (chain == NULL) {
		fprintf(stderr, "Error in memory allocairion.\n");
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

void addHandler(struct Handler *chain, enum event_type type, int (*handler)())
{
	struct Handler *current_handler = chain;

	while (current_handler->next)
		current_handler = current_handler->next;
		
	struct Handler *new_handler = (struct Handler *)malloc(sizeof(struct Handler));
	new_handler->type = type;
	new_handler->handler = handler;
	new_handler->next = NULL;
	current_handler->next = new_handler;
}

void handleEvent(struct Handler *chain, struct Event *event)
{
	struct Handler *current_handler = chain;
	while (current_handler)
	{
		if (current_handler->type == event->type)
		{
			current_handler->handler(event);
			break;
		}

		current_handler = current_handler->next;
	}
}

//handlers are mainly intended for requesting certain function from dbconnector
//and parse retreived table or json file to union data
int authenticateAccount(struct Event *event) { printf("Handling event type AUTHENTICATE_ACCOUNT\n"); }
int getAccount(struct Event *event) { printf("Handling event GET_ACCOUNT\n"); }
int updateAccount(struct Event *event) { printf("Handling event UPDATE_ACCOUNT\n"); }
int deleteAccount(struct Event *event) { printf("Handling event DELETE_ACCOUNT\n"); }

int getOrderList(struct Event *event) { printf("Handling event GET_ORDER_LIST\n"); }
int selectOrder(struct Event *event) { printf("Handling event SELECT_ORDER\n"); }
int finishOrder(struct Event *event) { printf("Handling event FINISH_ORDER\n"); }

int getMenu(struct Event *event) { printf("Handling event GET_MENU\n"); }
int addMeal(struct Event *event) { printf("Handling event ADD_MEAL\n"); }
int updateMeal(struct Event *event) { printf("Handling event UPDATE_MEAL\n"); }
int deleteMeal(struct Event *event) { printf("Handling event DELETE_MEAL\n"); }

int getRestaurantList(struct Event *event) { printf("Handling event GET_RESTAURANTS_LIST\n"); }
int viewCart(struct Event *event) { printf("Handling event VIEW_CART\n"); }
int addItem(struct Event *event) { printf("Handling event ADD_ITEM\n"); }
int updateItem(struct Event *event) { printf("Handling event UPDATE_ITEM\n"); }
int deleteItem(struct Event *event) { printf("Handling event DELETE_ITEM\n"); }
int orderCart(struct Event *event) { printf("Handling event ORDER_CART\n"); }

int getDeliveryList(struct Event *event) { printf("Handling event GET_DELIVERY_LIST\n"); }
int chooseDelivery(struct Event *event) { printf("Handling event CHOOSE_DELIVERY\n"); }
int withdrawDelivery(struct Event *event) { printf("Handling event WITHDRAW_DELIVERY\n"); }
int finishDelivery(struct Event *event) { printf("Handling event FINISH_DELIVERY\n"); }

