#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close()

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
                        
int main(int argc, char * argv[])
{
	char *ip = "127.0.0.1";
	int port = 5566;
 
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
 
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
		exit(1);
	printf("TCP server socket created.\n");
 
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);
 
	if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		exit(1);
	printf("Bound to the port number: %d\n", port);
 
	if (listen(server_sock, 1) < 0)
		exit(1);
	printf("Listening...\n");
 
	addr_size = sizeof(client_addr);
	client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
	if (client_sock < 0)
		exit(1);
	printf("Client connected.\n");
 
	if (close(client_sock) < 0)
		exit(1);
	printf("Client disconnected.\n");
	
	if (close(server_sock) < 0)
		exit(1);
	printf("Server was stopped.\n");
 
	return 0;
}




/*

	struct SOCKET_MESSAGE {
		message_type type; write or read
		union {
			foodle_restaurant_t rest;
			foodle_menu_t menu;
			foodle_menu_item_t item;
			string s;
		} data;
	}

	#include "foodle_db.h"
	if (type == read) {
		foodle_restaurant_t = foodle_db_restaurant_save("Aziz Meals");
	}

*/