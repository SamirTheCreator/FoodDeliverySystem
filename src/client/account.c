#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodle_types.h"
#include "account.h"

extern int server_socket;
extern struct foodle_event_t event;
extern union foodle_data_u data;

int authenticateAccount(char *name, char *password)
{
	event.type = AUTHENTICATE_ACCOUNT;
	strcpy(event.data.account.name, name);
	strcpy(event.data.account.password, password);

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), 0) == 0)
		return 0;

	return data.account.clientID;
}

struct foodle_account_t getAccount(int clientID)
{
	event.type = GET_ACCOUNT;
	event.data.account.clientID = clientID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return (struct foodle_account_t){};

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return (struct foodle_account_t){};

	return data.account;
}

int updateAccount(struct foodle_account_t account)
{
	event.type = UPDATE_ACCOUNT;
	event.data.account = account;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

int deleteAccount(int clientID)
{
	event.type = DELETE_ACCOUNT;
	event.data.account.clientID = clientID;

	if (send(server_socket, &event, sizeof(event), 0) == 0)
		return 0;

	if (recv(server_socket, &data, sizeof(data), MSG_WAITALL) == 0)
		return 0;

	return 1;
}

