#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 2000

int client_socket;
pthread_t receive_thread;

// Função para receber mensagens do servidor
void *receive_messages(void *arg) {
    char server_message[2000];
    memset(server_message, '\0', sizeof(server_message));

    while (1) {
        if (recv(client_socket, server_message, sizeof(server_message), 0) < 0) {
            printf("Server disconnected\n");
            break;
        }

        printf("Received from server: %s\n", server_message);
        memset(server_message, '\0', sizeof(server_message));
    }

    pthread_exit(NULL);
}

int main(void) {
    struct sockaddr_in server_addr;

    // Create socket:
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server:
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Couldn't connect to the server\n");
        return -1;
    }
    printf("Connected to the server\n");

    // Create a thread to receive messages from the server
    if (pthread_create(&receive_thread, NULL, receive_messages, NULL) < 0) {
        printf("Error creating thread\n");
        return -1;
    }

    char client_message[2000];

    while (1) {
        printf("Enter your message: ");
        fgets(client_message, sizeof(client_message), stdin);

        if (send(client_socket, client_message, strlen(client_message), 0) < 0) {
            printf("Can't send message\n");
            break;
        }

        memset(client_message, '\0', sizeof(client_message));
    }

    // Close the client socket:
    close(client_socket);

    return 0;
}
