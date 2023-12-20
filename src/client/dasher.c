#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "data_transfer.h"
#include "dasher.h"

extern struct foodle_event_t event;
extern union foodle_data_u data;

int getDeliveryList(void)
{
	event.type = GET_DELIVERY_LIST;

	return transfer(&event, &data);
}

int chooseDelivery(int dasherID, int orderID)
{
	event.type = CHOOSE_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	return transfer(&event, &data);
}

int withdrawDelivery(int dasherID, int orderID)
{
	event.type = WITHDRAW_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	return transfer(&event, &data);
}

int finishDelivery(int dasherID, int orderID)
{
	event.type = FINISH_DELIVERY;
	event.data.order.dasherID = dasherID;
	event.data.order.ID = orderID;

	return transfer(&event, &data);
}
