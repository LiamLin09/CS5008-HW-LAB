// CS 5008 Assignment 7 Networking
// Author: Nianlong Lin
// Date: 10/22/2023

#include <stdio.h>
#include <Stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// function to execute commands received from client.
void execute_command(int client_socket) {
    char buffer[128];
    while (1) {
        // receive data from client
        int read_size = recv(client_socket, buffer, sizeof(buffer), 0);
        // check if client has disconnected
        if (read_size == 0) {
            printf("Client disconnected.\n");
            break;
        } else if (read_size == -1) {
            perror("recv");
            break;
        }
        // null-terminate the received data
        buffer[read_size] = '\0';
        printf("Client sent: %s", buffer);
        // check for exit command to break the loop
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Exiting process.\n");
            break;
        }
        // execute the received command
        system(buffer);
    }
}

int main() {
    // create a socket.
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    // bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("bind");
        return 1;
    }

    if(listen(server_socket, 27) == -1) {
        perror("listen");
        return 1;
    }

    printf("Server is listening on Port 9002..\n");

    while (1) {
        // accept the connection
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        printf("Client has joined: %d\n", client_socket);
        // send the welcome message
        char welcome_message[] = "You have reached the server\n";
        send(client_socket, welcome_message, sizeof(welcome_message), 0);

        // create a child process to handle the client
        if (fork() == 0) {
            close(server_socket);
            execute_command(client_socket);
            close(client_socket);
            exit(0);
        } else {
            close(client_socket);
        }
    }

    close(server_socket);

    return 0;
}