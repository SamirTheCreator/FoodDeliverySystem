#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "user.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

int authenticateUser(char *name, char *password)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));

	event.type = AUTHENTICATE_USER;
	strcpy(event.data.user.name, name);
	strcpy(event.data.user.password, password);

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return data.user.userID;
}

struct foodle_user_t getUserInfo(int userID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_USER_INFO;
	event.data.user.userID = userID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_user_t){};

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return (struct foodle_user_t){};

	return data.user;
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

int deleteUserInfo(int userID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = DELETE_USER_INFO;
	event.data.user.userID = userID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

