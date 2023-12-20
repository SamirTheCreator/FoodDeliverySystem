#include <sys/socket.h>
#include "foodle_types.h"
#include "data_transfer.h"

extern int server_socket;

int transfer(struct foodle_event_t *event, union foodle_data_u *data)
{
	if (send(server_socket, event, sizeof(struct foodle_event_t), 0) == 0)
		return 0;

	if (recv(server_socket, data, sizeof(union foodle_data_u), MSG_WAITALL) == 0)
		return 0;
	
	return 1;
}
