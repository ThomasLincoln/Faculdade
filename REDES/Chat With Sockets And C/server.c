#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CLIENTS 10 // Defina o número máximo de clientes

int client_sockets[MAX_CLIENTS];
int num_clients = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Função de tratamento de cliente
void *handle_client(void *socket_desc) {
    int client_sock = *((int *)socket_desc);
    char client_message[2000];
    memset(client_message, '\0', sizeof(client_message));

    while (1) {
        // Receba a mensagem do cliente:
        if (recv(client_sock, client_message, sizeof(client_message), 0) < 0) {
            printf("Couldn't receive\n");
            break;
        }

        printf("Msg from client: %s\n", client_message);

        // Envie a mensagem para todos os outros clientes:
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < num_clients; i++) {
            if (client_sockets[i] != client_sock) {
                if (send(client_sockets[i], client_message, strlen(client_message), 0) < 0) {
                    printf("Failed to send message to a client\n");
                }
            }
        }
        pthread_mutex_unlock(&mutex);

        // Limpe o buffer para a próxima mensagem:
        memset(client_message, '\0', sizeof(client_message));
    }

    // Remova o soquete do cliente da lista de clientes:
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < num_clients; i++) {
        if (client_sockets[i] == client_sock) {
            for (int j = i; j < num_clients - 1; j++) {
                client_sockets[j] = client_sockets[j + 1];
            }
            num_clients--;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    close(client_sock);
    pthread_exit(NULL);
}

int main(void) {
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    pthread_t thread_id;

    // Clean buffer:
    char client_message[2000];
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the set port and IP:
    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    if (listen(socket_desc, 5) < 0) {
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");

    while (1) {
        // Accept an incoming connection:
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);

        if (client_sock < 0) {
            printf("Can't accept\n");
            return -1;
        }

        // Adicione o novo soquete do cliente à lista de clientes:
        pthread_mutex_lock(&mutex);
        if (num_clients < MAX_CLIENTS) {
            client_sockets[num_clients++] = client_sock;
        } else {
            printf("Max clients reached. Connection refused.\n");
            close(client_sock);
        }
        pthread_mutex_unlock(&mutex);

        printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Crie uma nova thread para lidar com o cliente:
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_sock) < 0) {
            printf("Error creating thread\n");
            return -1;
            
        }
    }

    // O servidor continuará ouvindo por novas conexões.

    return 0;
}
