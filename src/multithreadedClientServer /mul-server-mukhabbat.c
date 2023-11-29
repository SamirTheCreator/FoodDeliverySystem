/* server.c -- a program that recieves messages from multiple clients. It handles multiple socket connections with threads. */

#include <stdio.h>
#include <stdlib.h>		 // for EXIT_FAILURE
#include <sys/socket.h>  // for AF_INET, SOC_STREAM and other constants and data structures related to sockets 
#include <sys/types.h>   // for system data types
#include <netinet/in.h>  // for address structures 
#include <arpa/inet.h>   // for IP address
#include <unistd.h>		 // for close() and sleep() funciton
#include <string.h>		 // for strlen()
#include <pthread.h>	 // posix threads library, for creating threads

#define PORT 7777
#define STRMAX 255
#define MAXCLIENTS 5	 // the maximum number of clients

int active_clients = 0;	 // the number of active clients (connected to the server)

void * connection_handler(void * descr); // to handle connection for each client 

int main(void)
{

	/* Creating the socket with the socket() system call */
	
	int server_fd;	 // socket descriptor 
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(server_fd < 0)
	{
		perror("Creation of the server socket failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	puts("Server socket created!");
	
	/* Setting the socket options */
	
	int optval = 1, ret_val = 0;
	ret_val = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval));
	
	if(ret_val)
	{
		perror("Setting the socket option failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	
	/* Binding the socket to the address and port number specified in sockaddr_in */
	
	char * ip = "127.0.0.1";
	
	struct sockaddr_in address;		// defined in <netinet/in.h>
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip);
	address.sin_port = htons(PORT); // host to network short
	
	ret_val = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	
	if(ret_val < 0)
	{
		perror("Binding the socket to the address and port number is failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	printf("Bound to the port number %d\n", PORT);
	
	/* Listening on the socket for connections */
	
	int backlog = 5;
	ret_val = listen(server_fd, backlog);
	
	if(ret_val < 0)
	{
		perror("Listening on the socket for connection is failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	printf("Listening client on PORT %d\n", PORT);
	
	/* Accepting a new connection from a client */
	
	while (active_clients != MAXCLIENTS)
	{		
		int addr_length = sizeof(struct sockaddr_in);
		int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&(addr_length));
		
		if(new_socket < 0)
		{
			puts("Accepting a new connection is failed. Goodbye.");
			exit(EXIT_FAILURE);
		}
		printf("Server accepted a new connection on PORT: %d\n", PORT);
		
		pthread_t thread; // a thread identifier 
		ret_val = pthread_create(&thread, NULL, connection_handler, (void*)&new_socket); // create a new thread
		
		if(ret_val < 0)
		{
			perror("Creating a thread is failed. Goodbye.");
			exit(EXIT_FAILURE);
		}
		
		printf("New client [%d] connected.\n", new_socket);
		active_clients++;
	}
	
	if (close(server_fd) < 0)
	{
		puts("Failed to close server");
		exit(EXIT_FAILURE);
	}
	puts("Server closed");
	
	return 0;
}

/* Handle connection for each client */

void * connection_handler(void * descr)
{
	int sock = *(int *)descr;
    char buffer[STRMAX];
    int valread;
	char * hello = "Hello from the server!";
	
	send(sock, hello, strlen(hello), 0);
	valread = recv(sock, buffer, sizeof(buffer), 0);
	puts(buffer);
	
	while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        valread = recv(sock, buffer, sizeof(buffer), 0);
        if (valread == 0)
        {
            printf("Client [%d] disconnected\n", sock);
            active_clients--;
            break;
        }
        printf("Client [%d] message: %s\n", sock, buffer);
    }

    close(sock);
    return NULL;
}
