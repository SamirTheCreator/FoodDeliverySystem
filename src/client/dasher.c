#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "dasher.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

int getDeliveryList(void)
{
	event.type = GET_DELIVERY_LIST;

	if(send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

int chooseDelivery(int dasherID, int orderID)
{
	event.type = CHOOSE_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
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
