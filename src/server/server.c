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
	int client_sock;
	struct Handler *chain;
} thread_args;

extern struct Handler* initChainedHandler();
extern void handleEvent(struct Handler *chain, struct Event *event);

struct foodle_event_t event;
union foodle_data_u data;

int server_sock;
sem_t mutex;

void sig_handler(int signum)
{
	if (close(server_sock) < 0)
	{
		perror("Server socket was not closed");
		exit(1);
	}
	printf("\b\b  \nServer was stopped.\n");
	exit(0);
}

void* client_handler(void *vargp)
{
	int bytes_received, client_sock;
	struct Handler *chain;
	
	client_sock = thread_args.client_sock;
	chain = thread_args.chain;
	
	printf("Thread for client #%d was created\n", client_sock - 3);

	while (1)
	{
	  	sem_wait(&mutex);
		bytes_received = recv(client_sock, &event, sizeof event, MSG_WAITALL);
		sem_post(&mutex); 
		
		if (bytes_received == 0)
		{
			printf("Client disconnected.\n");
			break;
		}

		handleEvent(chain, &event);
		data = event.data; //should be in handler
		
		send(client_sock, &data, sizeof(data), 0);
	}
	
	return NULL;
}

int main(int argc, char * argv[])
{
	sem_init(&mutex, 0, 1);
	signal(SIGINT, sig_handler);
	
	//char *ip = "127.0.0.1";
	int port = 8080;
 
	int client_sock[MAXCLIENTS];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	
	pthread_t tid[MAXCLIENTS];
	struct Handler *chain;
 
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
	{
		perror("Server socket wasn't created");
		exit(1);
	}
	printf("TCP server socket created.\n");
 
	memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 0, 0);
 
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Server can't bind to port");
		exit(1);
	}
	printf("Bound to the port number: %d\n", port);
 
	if (listen(server_sock, MAXCLIENTS) < 0)
	{
		perror("Listen failed");
		exit(1);
	}
	printf("Listening...\n");

	if ((chain = initChainedHandler()) == NULL)
	{
		fprintf(stderr, "Failed to initialize handlers\n");
		exit(1);
	}

	for (int i = 0; i < MAXCLIENTS; ++i)
	{
		addr_size = sizeof(client_addr);
		client_sock[i] = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
		if (client_sock[i] < 0)
		{
			perror("Client socket was not created");
			exit(1);
		}
		printf("Client connected.\n");

		thread_args = (struct thread_args){ client_sock[i], chain };
		pthread_create(&tid[i], NULL, client_handler, 0);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i)
	{
		pthread_join(tid[i], NULL);
		printf("Thread for client %d terminated.\n", client_sock[i] - 3);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i)
	{
		if (close(client_sock[i]) < 0)
		{
			perror("Client socket was not closed");
			exit(1);
		}
		printf("Client %d disconnected.\n", i);
	}
	
	if (close(server_sock) < 0)
		exit(1);
	printf("Server was stopped.\n");
 
	sem_destroy(&mutex);
	return 0;
}

