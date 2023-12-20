#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handlers.h"
#include "foodle_db.h"

extern MYSQL *con;
extern struct foodle_event_t event;
extern union foodle_data_u data;

struct foodle_handler_t* initHandlers()
{
	struct foodle_handler_t *chain = malloc(sizeof(struct foodle_handler_t));
	if (chain == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		return NULL;
	}
	chain->type = -1;
	chain->next = NULL;
	
	addHandler(chain, AUTHENTICATE_USER, authenticateUser);
	addHandler(chain, ADD_USER_INFO, addUserInfo);
	addHandler(chain, GET_USER_INFO, getUserInfo);
	
	addHandler(chain, ADD_MEAL, addMeal);
	addHandler(chain, GET_MEAL, getMeal);
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

void addHandler(struct foodle_handler_t *chain, enum foodle_event_type_e type, int (*handler)(struct foodle_event_t *))
{
	struct foodle_handler_t *current_handler = chain;
	while (current_handler->next)
		current_handler = current_handler->next;
		
	struct foodle_handler_t *new_handler = (struct foodle_handler_t *)malloc(sizeof(struct foodle_handler_t));
	new_handler->type = type;
	new_handler->handler = handler;
	new_handler->next = NULL;
	current_handler->next = new_handler;
}

int handleEvent(struct foodle_handler_t *chain, struct foodle_event_t *event)
{	
	struct foodle_handler_t *current_handler = chain;
	while (current_handler) {
		if (current_handler->type == event->type)
			return current_handler->handler(event);

		current_handler = current_handler->next;
	}
	
	return 0;
}

int authenticateUser(struct foodle_event_t *event)
{
	printf("[>] Handling event type AUTHENTICATE_USER\n");

	struct foodle_user_t *user = foodle_db_get_user_byphone(con, event->data.user.phone);
	if (user == NULL)
		return 0;
	
	printf("[<] Successfully handled AUTHENTICATE_USER\n");
	data.user = *user;
	free(user);
	if (strcmp(event->data.user.password, data.user.password))
		data.user.ID = -1;

	return 1;
}

int addUserInfo(struct foodle_event_t *event)
{
	printf("[>] Handling event type ADD_USER_INFO\n");
	foodle_db_add_user(con, &event->data.user);
	struct foodle_user_t *user = foodle_db_get_user_byphone(con, event->data.user.phone);
	if (user == NULL)
		return 0;
		
	printf("[<] Successfully handled ADD_USER_INFO\n");
	data.user = *user;
	free(user);
	
	return 1;
}

int getUserInfo(struct foodle_event_t *event)
{
	printf("[>] Handling event type GET_USER_INFO\n");
	struct foodle_user_t *user = foodle_db_get_user_byid(con, event->data.user.ID);
	if (user == NULL)
		return 0;
		
	printf("[<] Successfully handled GET_USER_INFO\n");
	data.user = *user;
	free(user);
	
	return 1;
}

int getMeal(struct foodle_event_t *event)
{
	printf("[>] Handling event type GET_MEAL\n");
	struct foodle_meal_t *meal = foodle_db_get_meal_byid(con, event->data.meal.ID);
	if (meal == NULL)
		return 0;
		
	printf("[<] Successfully handled GET_MEAL\n");
	data.meal = *meal;
	free(meal);	
	return 1;
}

int addMeal(struct foodle_event_t *event)
{
	printf("[>] Handling event type ADD_MEAL\n");
	foodle_db_add_meal(con, &event->data.meal, event->data.restaurant.ID);
	struct foodle_meal_t *meal = foodle_db_get_meal_byid(con, event->data.restaurant.ID);
	if (meal == NULL)
		return 0;
	
	printf("[<] Successfully handled ADD_MEAL\n");	
	data.meal = *meal;
	free(meal);
	
	return 1;
}

int updateMeal(struct foodle_event_t *event)
{
	printf("[>] Handling event type UPDATE_MEAL\n");
	foodle_db_update_meal_bystruct(con, &event->data.meal);
	struct foodle_meal_t *meal = foodle_db_get_meal_byid(con, event->data.meal.ID);
	if (meal == NULL)
		return 0;
	
	printf("[<] Successfully handled UPDATE_MEAL\n");	
	data.meal = *meal;
	free(meal);
	
	return 1;
}

int deleteMeal(struct foodle_event_t *event)
{
	printf("[>] Handling event type DELETE_MEAL\n");
	foodle_db_delete_meal_byid(con, event->data.meal.ID);
	struct foodle_meal_t *meal = foodle_db_get_meal_byid(con, event->data.meal.ID);
	if (meal != NULL)
		return 0;
	
	printf("[<] Successfully handled DELETE_MEAL\n");
	
	return 1;
}

int getOrderList(struct foodle_event_t *event)
{
	printf("    Handling event type GET_ORDER_LIST\n");
	data.order_list[0] = (struct foodle_order_t){};
}

int selectOrder(struct foodle_event_t *event)
{
	printf("    Handling event type SELECT_ORDER\n");
	data.order.restaurantID = 1;
	strcpy(data.order.status, str(Preparing));
}

int finishOrder(struct foodle_event_t *event)
{
	printf("    Handling event FINISH_ORDER\n");
	strcpy(data.order.status, str(Finished));
}

int getRestaurantList(struct foodle_event_t *event) { printf("Handling event type GET_RESTAURANT_LIST\n"); }

int getMenu(struct foodle_event_t *event)
{
	printf("[>] Handling event type GET_MENU\n");
	struct foodle_menu_t *menu = foodle_db_get_menu(con, event->data.restaurant.ID);
	if (menu == NULL)
		return 0;
		
	printf("[<] Successfully handled GET_MENU\n");	
	data.menu = *menu;
	free(menu);
	
	return 1;
}

int orderCart(struct foodle_event_t *event) { printf("    Handling event type ORDER_CART\n"); }
int getDeliveryList(struct foodle_event_t *event) { printf("    Handling event type GET_DELIVERY_LIST\n"); }
int chooseDelivery(struct foodle_event_t *event) { printf("    Handling event type CHOOSE_DELIVERY\n"); }
int withdrawDelivery(struct foodle_event_t *event) { printf("Handling event type WITHDRAW_DELIVERY\n"); }
int finishDelivery(struct foodle_event_t *event) { printf("Handling event type FINISH_DELIVERY\n"); }

