#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "dasher.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

struct foodle_delivery_t* getDeliveryList(void)
{
	event.type = GET_DELIVERY_LIST;

	if(send(server_socket, &event, sizeof(event), 0) == 0)
		return NULL;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return NULL;

	return data.delivery_list;
}

struct foodle_delivery_t chooseDelivery(int dasherID, int orderID)
{
	event.type = CHOOSE_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_delivery_t){};

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return (struct foodle_delivery_t){};

	return data.delivery;
}

int withdrawDelivery(int dasherID, int orderID)
{
	event.type = WITHDRAW_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	if (send(server_socket, &event, sizeof event, 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof data, MSG_WAITALL) == 0)
		return 0;
    
	return 1;
}

int finishDelivery(int dasherID, int orderID)
{
	event.type = FINISH_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;
        
	return 1;
}
