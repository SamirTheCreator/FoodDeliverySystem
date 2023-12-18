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
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = ADD_MEAL;
	event.data.restaurant.ID = restaurantID;
	strcpy(event.data.meal.name, meal_name);
	event.data.meal.price = price;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return data.meal.ID;
}

int getMeal(int mealID, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_MEAL;
	event.data.restaurant.ID = restaurantID;
	event.data.meal.ID = mealID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return data.meal.ID;
}

int updateMeal(int mealID, char* meal_name, float price, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = UPDATE_MEAL;
	event.data.restaurant.ID = restaurantID;
	event.data.meal.ID = mealID;
	strcpy(event.data.meal.name, meal_name);
	event.data.meal.price = price;
	
	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

    return 1;
}

int deleteMeal(int mealID, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = DELETE_MEAL;
	event.data.meal.ID = mealID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

struct foodle_order_t* getOrderList(void)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_ORDER_LIST;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return NULL;

	return &data.order;
}

struct foodle_order_t selectOrder(int orderID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = SELECT_ORDER;
	event.data.order.ID = orderID;
	strcpy(event.data.order.status, str(Preparing));

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_order_t){};

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return (struct foodle_order_t){};

	return data.order;
}

int finishOrder(int orderID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = FINISH_ORDER;
	event.data.order.ID = orderID;
    
	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

