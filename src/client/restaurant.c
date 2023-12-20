#include <stdio.h>
#include <string.h>

#include "foodle_types.h"
#include "data_transfer.h"
#include "restaurant.h"

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

	return transfer(&event, &data);
}

int getMeal(int mealID, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_MEAL;
	event.data.restaurant.ID = restaurantID;
	event.data.meal.ID = mealID;

	return transfer(&event, &data);
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
	
	return transfer(&event, &data);
}

int deleteMeal(int mealID, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = DELETE_MEAL;
	event.data.restaurant.ID = restaurantID;
	event.data.meal.ID = mealID;

	return transfer(&event, &data);
}

int getOrderList(void)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_ORDER_LIST;

	return transfer(&event, &data);
}

int selectOrder(int orderID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = SELECT_ORDER;
	event.data.order.ID = orderID;
	strcpy(event.data.order.status, str(Preparing));

	return transfer(&event, &data);
}

int finishOrder(int orderID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = FINISH_ORDER;
	event.data.order.ID = orderID;
    
	return transfer(&event, &data);
}

