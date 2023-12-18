#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "account.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

int authenticateUser(struct foodle_user_t user)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));

	event.type = AUTHENTICATE_USER;
	event.data.user = user;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

int getUserInfo(struct foodle_user_t user)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_USER_INFO;
	event.data.user = user;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

int updateUserInfo(struct foodle_user_t user)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = UPDATE_USER_INFO;
	event.data.user = user;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

int deleteUserInfo(struct foodle_user_t user)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = DELETE_USER_INFO;
	event.data.user = user;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

