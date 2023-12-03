#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 256

// Structure to hold client information
typedef struct {
    int client_socket;
} ClientInfo;

// Function to handle client messages
void *handleClient(void *arg) {
    ClientInfo *client = (ClientInfo *)arg;
    char buffer[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = recv(client->client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        printf("Client: %s", buffer);
    }

    close(client->client_socket);
    free(client);
    pthread_exit(NULL);
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for clients
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening..\n");

    // Accept and handle clients
    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        // Create a thread for each client
        pthread_t thread;
        ClientInfo *client_info = (ClientInfo *)malloc(sizeof(ClientInfo));
        client_info->client_socket = client_socket;

        if (pthread_create(&thread, NULL, handleClient, (void *)client_info) != 0) {
            perror("Thread creation failed");
            close(client_socket);
            free(client_info);
        }
    }

    close(server_socket);
    return 0;
}
