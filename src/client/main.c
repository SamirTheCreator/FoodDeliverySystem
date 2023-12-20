#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close(), sleep()

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "foodle_types.h"
#include "account.h"
#include "restaurant.h"
#include "customer.h"
#include "dasher.h"

int server_socket;
struct foodle_event_t event;
union foodle_data_u data;

int main(int argc, char *argv[])
{
	int port = argc > 1 ? atoi(argv[1]) : 8080;
	char *ip = argc > 2 ? argv[2] : "127.0.0.1";

	struct sockaddr_in addr;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		perror("[!] Socket for server wasn't created");
		exit(1);
	}
	printf("[+] TCP socket for server was created\n");

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)	{
		perror("[!] Failed to connect to the server");
		exit(1);
	}
	printf("[+] Connected to the server\n");

	if (close(server_socket) < 0) {
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("[-] Disconnected from the server\n");

	return 0;
}
