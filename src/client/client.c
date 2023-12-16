#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close()

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "foodle_types.h"
#include "account.h"
#include "customer.h"
#include "dasher.h"
#include "restaurant.h"

int server_socket;
struct foodle_event_t event;
union foodle_data_u data;

int main(int argc, char * argv[])
{
	//char *ip = "127.0.0.1";
	int port = 8888;

	struct sockaddr_in addr;
	socklen_t addr_size;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		perror("Socket for server wasn't created");
		exit(1);
	}
	printf("TCP socket for server was created.\n");

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = INADDR_ANY;

	if (connect(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		exit(1);
	printf("Connected to the server.\n");
		
		
	/////////////////////////////////////////////////////////
	//Here you write your logic for client
	#include "authorization.c"
	////////////////////////////////////////////////////////

	
	if (close(server_socket) < 0)	{
		perror("Server socket was not closed");
		exit(1);
	}
	printf("Disconnected from the server.\n");

	return 0;
}

