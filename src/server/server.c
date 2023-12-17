#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close()
#include <signal.h>     //SIGINT, signal()
#include <pthread.h>    //pthread_t, pthread_create(), pthread_join()
#include <semaphore.h>  //sem_t, sem_init(), sem_wait(), sem_post(), sem_destroy()
#include <errno.h>      //perror()

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "foodle_types.h"

#define MAXCLIENTS 10

struct thread_args {
	int client_socket;
	struct Handler *chain;
} thread_args;

extern struct Handler* initChainedHandler();
extern int handleEvent(struct Handler *chain, struct foodle_event_t *event);

struct foodle_event_t event;
union foodle_data_u data;

int server_sock;
sem_t mutex;

void sig_handler(int signum)
{
	if (close(server_sock) < 0)	{
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("\b\b  \n[-] Server was stopped.\n");
	exit(0);
}

void* client_handler(void *vargp)
{
	int bytes_received, client_socket;
	struct Handler *chain;
	
	client_socket = thread_args.client_socket;
	chain = thread_args.chain;
	
	printf("[+] Thread for client #%d was created\n", client_socket - 3);

	while (1) {
	  	//sem_wait(&mutex);
		bytes_received = recv(client_socket, &event, sizeof(event), MSG_WAITALL);
		
		if (bytes_received <= 0) {
			fprintf(stderr, "[-] Client #%d disconnected.\n", client_socket - 3);
			//sem_post(&mutex);
			break;
		}

		printf("%d KB event was received from client #%d\n", bytes_received / 1024, client_socket - 3);
		memset(&data, 0, sizeof(data));
		if (!handleEvent(chain, &event))
			printf("[?] Failed to handle event\n");
		
		send(client_socket, &data, sizeof(data), 0);
		//sem_post(&mutex);
	}
	
	return NULL;
}

int main(int argc, char * argv[])
{
	sem_init(&mutex, 0, 1);
	signal(SIGINT, sig_handler);
	
	//char *ip = "127.0.0.1";
	int port = 8080;
 
	int client_socket[MAXCLIENTS];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	
	pthread_t tid[MAXCLIENTS];
	struct Handler *chain;
 
 	//MYSQL *con = foodle_db_init();
 
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("[!] Socket for server wasn't created");
		exit(1);
	}
	printf("[+] TCP socket for server was created.\n");
 
	memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 0, 0);
 
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("[!] Server can't bind to port");
		exit(1);
	}
	printf("[+] Bound to the port number: %d\n", port);
 
	if (listen(server_sock, 1) < 0)	{
		perror("[!] Listen failed");
		exit(1);
	}
	printf("[+] Listening...\n");

	chain = initChainedHandler();
	if (chain == NULL) {
		fprintf(stderr, "[!] Failed to initialize handlers.\n");
		exit(1);
	}

	for (int i = 0; i < MAXCLIENTS; ++i) {
		addr_size = sizeof(client_addr);
		client_socket[i] = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
		if (client_socket[i] < 0)	{
			perror("[!] Socket for client was not created");
			exit(1);
		}
		printf("[+] Client #%d connected.\n", client_socket[i] - 3);

		thread_args = (struct thread_args){ client_socket[i], chain };
		pthread_create(&tid[i], NULL, client_handler, 0);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i) {
		pthread_join(tid[i], NULL);
		printf("[-] Thread for client %d terminated.\n", client_socket[i] - 3);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i) {
		if (close(client_socket[i]) < 0) {
			perror("[!] Client socket was not closed");
			exit(1);
		}
		printf("[-] Client #%d disconnected.\n", client_socket[i] - 3);
	}
	
	if (close(server_sock) < 0)
		exit(1);
	printf("[-] Server was stopped.\n");
	
	//mysql_close(con);
 
	sem_destroy(&mutex);
	return 0;
}

