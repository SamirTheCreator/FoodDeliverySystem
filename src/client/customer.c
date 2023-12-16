#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "customer.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

void viewCart(void)
{
	event.type = VIEW_CART;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return;

	//printing the cart
	printf("Cart:\n");
	for(int i = 0; i < data.cart.item[i].quantity; i++)
		printf("%d. %s\n", i+1, data.cart.item[i].meal.name);
}

int addItem(int itemID, int quantity)
{
	event.type = ADD_ITEM;
	event.data.item.meal.mealID = itemID;
	event.data.item.quantity = quantity;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return 0;

	return 1;
}

int deleteItem(int itemID)
{
	event.type = DELETE_ITEM;
	event.data.item.meal.mealID = itemID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return 0;

	return 1;
}

int updateItem(int itemID, int quantity)
{
	event.type = UPDATE_ITEM;
	event.data.item.meal.mealID = itemID;
	event.data.item.quantity = quantity;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return 0;

	return 1;
}

struct foodle_order_t* orderCart(int customerID, struct foodle_order_t order, char *address)
{
	event.type = ORDER_CART;
	event.data.order.customerID = customerID;
	event.data.order.cart = order.cart;
	strcpy(event.data.order.address, address);

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return NULL;
       
	return &data.order;
}

struct foodle_restaurant_t* getRestaurantList(void)
{
	event.type = GET_RESTAURANT_LIST;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return NULL;

	return data.restaurant_list;
}

struct foodle_menu_t* getMenu(int restaurantID) {
	event.type = GET_MENU;
	event.data.restaurant.restaurantID = restaurantID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return NULL;

	return &data.menu;
}

