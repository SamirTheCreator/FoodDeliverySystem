#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "data_transfer.h"
#include "customer.h"

extern struct foodle_event_t event;
extern union foodle_data_u data;

void viewCart(void)
{
	//printing the cart
	printf("Cart:\n");
	for(int i = 0; i < data.order.cart.item[i].quantity; i++)
		printf("%d. %s\n", i+1, data.order.cart.item[i].meal.name);
}

int getRestaurantList(void)
{
	event.type = GET_RESTAURANT_LIST;

	return transfer(&event, &data);
}

int getMenu(int restaurantID)
{
	event.type = GET_MENU;
	event.data.restaurant.ID = restaurantID;

	return transfer(&event, &data);
}

int orderCart(struct foodle_order_t order)
{
	event.type = ORDER_CART;
	event.data.order = order;

	return transfer(&event, &data);
}

