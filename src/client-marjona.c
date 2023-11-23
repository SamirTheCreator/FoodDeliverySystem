#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>
#include<unistd.h>

struct msg {
	char ip4_addr[16];
	int port;
	char str[255];
};

int main() {
	 // here I create a socket for server
	 int network_socket;
	 network_socket = socket(AF_INET, SOCK_STREAM, 0);
	  
	 // now I have to specify an address for the socket
	 struct sockaddr_in server_address;
	 server_address.sin_family = AF_INET;
	 server_address.sin_port = htons(9002);
	 server_address.sin_addr.s_addr = INADDR_ANY;
	 
	 
	 int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	 // checking for error with the connection 
	 if (connection_status == -1) {
	 printf("Connection error\n\n");
	 exit(1);
	 }	
	  
	 struct msg message;
	 
	 while(1){
	 // receive data  from the server
	 recv(network_socket, &message, sizeof(message), 0);
	 // to print the server's responce
	 printf("From server: %s\n", message.str);
	 
	 
	 message.port = 9002;
	 strcpy(message.ip4_addr,  "127.0.0.1");
	 printf("To server: ");
	 scanf("%s", message.str);
	 send(network_socket, &message, sizeof(message), 0);
	 }
  	
	 // to close the socket
	 close(network_socket);
	 
	 
	 
	 return 0;

}

