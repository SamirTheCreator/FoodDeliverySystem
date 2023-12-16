#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "restaurant.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

int addMeal(char *meal_name, float price, int restaurantID)
{
	event.type = ADD_MEAL;
	event.data.restaurant.restaurantID = restaurantID;
	strcpy(event.data.meal.name, meal_name);
	event.data.meal.price = price;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == MSG_WAITALL)
		return 0;

	return data.meal.mealID;
}

int deleteMeal(int mealID, int restaurantID)
{
	event.type = DELETE_MEAL;
	event.data.meal.mealID = mealID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == MSG_WAITALL)
		return 0;

	return 1;
}

int updateMeal(int mealID, char* meal_name, float price, int restaurantID)
{
	event.type = UPDATE_MEAL;
	event.data.restaurant.restaurantID = restaurantID;
	strcpy(event.data.meal.name, meal_name);
	event.data.meal.price = price;
	event.data.meal.mealID = mealID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == MSG_WAITALL)
		return 0;

    return 1;
}

struct foodle_order_t* getOrderList(void)
{
	event.type = GET_ORDER_LIST;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), 0) == MSG_WAITALL)
		return NULL;

	return &data.order;
}

struct foodle_order_t selectOrder(int orderID)
{
	event.type = SELECT_ORDER;
	event.data.order.orderID = orderID;
	event.data.order.status = Preparing;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_order_t){};

	if (recv(server_socket, &data, sizeof(data), 0) == MSG_WAITALL)
		return (struct foodle_order_t){};

	return data.order;
}

int finishOrder(int orderID)
{
	event.type = FINISH_ORDER;
	event.data.order.orderID = orderID;
    
	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == MSG_WAITALL)
		return 0;

	return 1;
}

