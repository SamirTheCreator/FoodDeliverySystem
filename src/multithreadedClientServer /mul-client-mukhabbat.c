/* client.c -- a C program that uses socket programming to create a client process */

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
		puts("Creation of the client socket failed. Goodbye.");
		return -1;
	}
	puts("Client socket created!");
	
	/* Defining the socket options */
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
		puts("Connection on the socket for communication with server faild");
      	return -1;
    }
	printf("Connected to the server on port %d\n", PORT);
	
	/* Sending and recieving the data */
	
	char message[STRMAX];
	int bye_typed = 0;
	char * hello = "Hello from the client!";
	char * bye = "Bye";
	int valread;
	
	send(sock, hello, strlen(hello), 0);
	valread = recv(sock, message, sizeof(message), 0);
	puts(message);
	
	while(!bye_typed)
	{
		memset(message, 0, sizeof(message)); 	   // clear the previous data in the message
		printf("Client: ");
		if (s_gets(message, sizeof(message)))
		{
			send(sock, message, strlen(message), 0);
			
			if(strncmp(message, bye, strlen(bye)) == 0)
				bye_typed = 1; // server has typed "Bye"
		}
		else
		{
			puts("End of file encountered!");
			break;
		}
	}
	
	if (close(sock) < 0)
	{
		puts("Failed to close the server");
		exit(EXIT_FAILURE);
	}
	puts("Server connection closed.");
	
	return 0;
}

/* get input */

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
