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

	int sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		exit(1);
	printf("TCP server socket created.\n");

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		exit(1);
	printf("Connected to the server.\n");
 
	if (close(sock) < 0)
		exit(1);
	printf("Disconnected from the server.\n");

	return 0;
}

