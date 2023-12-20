#include <stdio.h>
#include <string.h>

#include "foodle_types.h"
#include "data_transfer.h"
#include "account.h"

extern struct foodle_event_t event;
extern union foodle_data_u data;

int authenticateUser(char *phone, char *password)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));

	event.type = AUTHENTICATE_USER;
	strncpy(event.data.user.phone, phone, 4); strcat(event.data.user.phone, " ");
	strncat(event.data.user.phone, phone + 4, 2); strcat(event.data.user.phone, " ");
	strncat(event.data.user.phone, phone + 6, 3); strcat(event.data.user.phone, " ");
	strncat(event.data.user.phone, phone + 9, 2); strcat(event.data.user.phone, " ");
	strncat(event.data.user.phone, phone + 11, 2);
	strncpy(event.data.user.password, password, 20);

	return transfer(&event, &data);
}

int addUserInfo(struct foodle_user_t user)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = ADD_USER_INFO;
	event.data.user = user;

	return transfer(&event, &data);
}

int getUserInfo(struct foodle_user_t user)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_USER_INFO;
	event.data.user = user;

	return transfer(&event, &data);
}

