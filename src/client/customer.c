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
	//printing the cart
	printf("Cart:\n");
	for(int i = 0; i < data.order.cart.item[i].quantity; i++)
		printf("%d. %s\n", i+1, data.order.cart.item[i].meal.name);
}

struct foodle_restaurant_t* getRestaurantList(void)
{
	event.type = GET_RESTAURANT_LIST;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return NULL;

	return data.restaurant_list;
}

struct foodle_menu_t getMenu(int restaurantID)
{
	event.type = GET_MENU;
	event.data.restaurant.ID = restaurantID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_menu_t){};

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return (struct foodle_menu_t){};

	return data.menu;
}

struct foodle_order_t orderCart(int customerID, struct foodle_order_t order, char *address)
{
	event.type = ORDER_CART;
	event.data.order.customerID = customerID;
	event.data.order.cart = order.cart;
	strcpy(event.data.order.address, address);

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_order_t){};

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return (struct foodle_order_t){};
       
	return data.order;
}

