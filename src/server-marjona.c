#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>

struct msg {
	char ip4_addr[16];
	int port;
	char str[255];
};

int main() {
 	char server_message[256] ;
 	char client_message[256] = {0};
 	// creating server socket
 	int server_socket;
 	server_socket = socket(AF_INET, SOCK_STREAM, 0);
 	printf("Server socket created\n");
 	
 	
 	// server address 
 	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//this is to bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("Bind to the port: 9002\n");
	
	listen(server_socket, 5);
	printf("I'm listening Amigoo.....\n");
	
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL );
	printf("Client is accepted. UUU yeeah\n");
	
	struct msg message;
	
	while(1){
	// send the message
	printf("To client: ");
	scanf("%s", message.str);
	strcpy(message.ip4_addr, "");
	message.port =  0;
	send(client_socket, &message, sizeof(message), 0);
	
	
	recv(client_socket, &message, sizeof(message), 0 );
	printf("From client: %s\n", message.str); 
	printf("Port Number: %d\n Ip address: %s\n", message.port, message.ip4_addr);
	}
	close(server_socket);
	


}
