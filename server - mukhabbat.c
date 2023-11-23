/* server.c -- a C program that that uses socket programming to create a server process */

#include <stdio.h>
#include <stdlib.h>		 // for EXIT_FAILURE
#include <sys/socket.h>  // for AF_INET, SOC_STREAM and other constants and data structures related to sockets 
#include <sys/types.h>   // for system data types
#include <netinet/in.h>  // for address structures 
#include <arpa/inet.h>   // for IP address
#include <unistd.h>		 // for close() funciton
#include <string.h>		 // for strlen()

#define PORT 7777		 // port numbers above 1024 are available for general use
#define STRMAX 255		 // maximum length of strings to be retrieved and send

char * s_gets(char * st, int size); // get input

int main(void)
{
	/* Creating the socket with the socket() system call */
	
	int server_fd;	 // socket descriptor 
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(server_fd < 0)
	{
		puts("Creation of the server socket is failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	puts("Server socket created!");
	
	/* Setting the socket options */
	
	int optval = 1, ret_val = 0;
	ret_val = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval));
	
	if(ret_val)
	{
		puts("Setting the socket option failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	/* Binding the socket to the address and port number specified in sockaddr_in */
	
	char * ip = "127.0.0.1";
	struct sockaddr_in address;		// defined in netinet/in.h
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip);
	address.sin_port = htons(PORT); // host to network short
	
	ret_val = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	
	if(ret_val < 0 )
	{
		puts("Binding the socket to the address and port number is failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	printf("Bound to the port number %d\n", PORT);
	
	/* Listening on the socket for connections */
	
	int backlog = 1;
	ret_val = listen(server_fd, backlog);
	
	if(ret_val < 0)
	{
		puts("Listening on the socket for connection is failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	printf("Listening client on PORT %d\n", PORT);
	
	/* Accepting a new connection from a client */
	
	int addr_length = sizeof(address);
	int new_socket = 0;
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&(addr_length));
	
	if(new_socket < 0)
	{
		puts("Accepting a new connection is failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	puts("Server accepted a new connection on PORT 7777");
	
	/* Sending and recieving the data */
	
	struct msg 
	{
		char ip4_addr[16];
		int port;
		char str[STRMAX];
	};
	
	struct msg buffer, schat;
	int valread = 0;
	char * hello = "Hello from the server!";
	char * bye = "Bye.";
	
	valread = read(new_socket, buffer.str, sizeof(buffer.str)); // hello message from Client(new_socket) has to be read
	puts(buffer.str); 								// print the hello message from client
	send(new_socket, hello, strlen(hello), 0);  	// send hello message to the Client(new_socket)
	puts("I'm ready for chat!");
	
	int bye_typed = 0;
	
	while(!bye_typed)
	{
		memset(buffer.str, 0, sizeof(buffer.str)); // clear the previous data in the buffer
		valread = read(new_socket, buffer.str, sizeof(buffer.str));
		puts(buffer.str);
		
		memset(schat.str, 0, sizeof(schat.str));   // set all bytes of an schat to 0
		printf("Server: ");
		s_gets(schat.str, sizeof(schat.str));
		send(new_socket, schat.str, strlen(schat.str), 0);
		
		if(strncmp(schat.str, bye, strlen(bye)) == 0)
			bye_typed = 1; // client has typed "Bye."
	}
	
	if (close(new_socket) < 0)
	{
		puts("Failed to close client");
		exit(EXIT_FAILURE);
	}
	puts("Client closed");
	
	if (close(server_fd) < 0)
	{
		puts("Failed to close server");
		exit(EXIT_FAILURE);
	}
	puts("Server closed");
	
	return 0;
}

/* get input from the client */

char * s_gets(char * st, int size) 
{
	char * ret_val;
	int i = 0;
	
	ret_val = fgets(st, size, stdin);
	if (ret_val)
	{
		while (st[i] != '\n' && st[i] != '\0')
			i++;
			
		if (st[i] == '\n')
			st[i] = '\0';
		else //  words[i] == '\0'
			while (getchar() != '\n')
				continue;
	}
	return ret_val;

}
