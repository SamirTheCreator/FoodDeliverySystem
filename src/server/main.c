#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close()
#include <signal.h>     //SIGINT, signal()
#include <pthread.h>    //pthread_t, pthread_create(), pthread_join()
#include <semaphore.h>  //sem_t, sem_init(), sem_wait(), sem_post(), sem_destroy()
#include <errno.h>      //perror()
#include <mysql.h>	//MYSQL

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "foodle_db.h"
#include "handlers.h"
#include "foodle_types.h"

#define MAXCLIENTS 10

struct thread_args {
	int client_counter;
	int client_socket;
	struct foodle_handler_t *chain;
};

struct foodle_event_t event;
union foodle_data_u data;

MYSQL *con;
int server_sock;
sem_t mutex;

void sig_handler(int signum)
{
	if (close(server_sock) < 0)	{
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("\b\b[-] Server was stopped.\n");
	exit(0);
}

void* client_handler(void *vargp)
{
	struct thread_args *thread_args = vargp;
	int bytes_received, client_socket, client_counter;
	struct foodle_handler_t *chain;
	
	client_counter = thread_args->client_counter;
	client_socket = thread_args->client_socket;
	chain = thread_args->chain;
	
	printf("[+] Thread for client #%d was created\n", client_counter);

	while (1) {
	  	//sem_wait(&mutex);
		bytes_received = recv(client_socket, &event, sizeof(event), MSG_WAITALL);
		
		if (bytes_received <= 0) {
			printf("[-] Client #%d stopped\n", client_counter);
			//sem_post(&mutex);
			return NULL;
		}

		printf("    From Client #%d was reveived event (%d KB)\n", client_counter, bytes_received / 1024);
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
	con = foodle_db_init();

	int port = argc > 1 ? atoi(argv[1]) : 8080;
	char *ip = argc > 2 ? argv[2] : "127.0.0.1";

	int client_socket[MAXCLIENTS];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	
	pthread_t tid[MAXCLIENTS];
	struct foodle_handler_t *chain;
	
	chain = initHandlers();
	if (chain == NULL) {
		fprintf(stderr, "[!] Failed to initialize handlers.\n");
		exit(1);
	}
 	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("[!] Socket for server wasn't created");
		exit(1);
	}
	printf("[+] TCP socket for server was created\n");
 
	memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	if (inet_aton(ip, &server_addr.sin_addr) == 0) {
		fprintf(stderr, "[!] Invalid IPv4 address\n");
		exit(1);
	}
	printf("[+] Asigned IPv4 address: %s\n", ip);
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

	for (int i = 0; i < MAXCLIENTS; ++i) {
		addr_size = sizeof(client_addr);
		client_socket[i] = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
		if (client_socket[i] < 0) {
			perror("[!] Socket for client was not created");
			exit(1);
		}
		printf("[+] Client #%d connected\n", i + 1);

		struct thread_args thread_args = { i + 1, client_socket[i], chain };
		pthread_create(&tid[i], NULL, client_handler, &thread_args);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i) {
		pthread_join(tid[i], NULL);
		printf("[-] Thread for client #%d terminated\n", i + 1);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i) {
		if (close(client_socket[i]) < 0) {
			perror("[!] Client socket was not closed");
			exit(1);
		}
		printf("[-] Client #%d disconnected\n", i + 1);
	}
	
	if (close(server_sock) < 0)
		exit(1);
	printf("[-] Server was stopped\n");
	
	mysql_close(con);
	sem_destroy(&mutex);

	return 0;
}

