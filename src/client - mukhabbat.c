/* server.c -- a C program that uses socket programming to create a client socket */

#include <stdio.h>
#include <stdlib.h>		 // for EXIT_FAILURE and EXIT_SUCCESS 
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
	/* Creating the client with the socket() system call */
	
	int sock = 0;	 // socket descriptor 
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sock < 0)
	{
		puts("Creation of the client socket is failed. Goodbye.");
		return -1;
	}
	puts("Client socket created!");
	
	/* Defining the socket options */
	
	struct sockaddr_in address;		// defined in netinet/in.h
	struct sockaddr_in serv_addr;
	memset(&serv_addr, '0', sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT); // host to network short
	
	const char * ip_addr = "127.0.0.1";
	int ret_result = inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr);
	
	if(ret_result <= 0) 
	{
		puts("Could not find the address.");
      	return -1;
    }
	
	/* Connecting on the socket for communication with server */
	
	ret_result = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	
	if (ret_result < 0)
	{
		puts("Connection on the socket for communication with server is faild");
      	return -1;
    }
	puts("Connected to the server on port 7777");
	
	/* Sending and recieving the data */
	
	struct msg 
	{
		char ip4_addr[16];
		int port;
		char str[STRMAX];
	};
	
	struct msg buffer, cchat;
	int valread = 0;
	char * hello = "Hello from the client!";
	char * bye = "Bye.";
	
	send(sock, hello, strlen(hello), 0);  		// send hello message to the Server(sock)
	valread = read(sock, buffer.str, sizeof(buffer.str)); 		// hello message from Server(sock) has to be read
	puts(buffer.str); 								// print the hello message from server
	puts("I'm ready for chat!");
	
	int bye_typed = 0;
	
	while(!bye_typed)
	{
		memset(buffer.str, 0, sizeof(buffer.str)); // clear the previous data in the buffer
		memset(cchat.str, 0, sizeof(cchat.str));   // set all bytes of an cchat to 0
		printf("Client: ");
		if (s_gets(cchat.str, sizeof(cchat.str)))
		{
			send(sock, cchat.str, strlen(cchat.str), 0);
			valread = read(sock, buffer.str, sizeof(buffer.str));
			puts(buffer.str);
		
			if(strncmp(cchat.str, bye, strlen(bye)) == 0)
				bye_typed = 1; // server has typed "Bye."
		}
		else
			puts("End of file encountered!");
	}
	
	if (close(sock) < 0)
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
