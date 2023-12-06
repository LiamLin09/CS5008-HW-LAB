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

int main() {

    // create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    // connect to the server    
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("connect");
        return 1;
    }

    // receive welcome message from server
    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response), 0);
    printf("%s", server_response);

    char username[32];
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n");

    printf("%s>", username);
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
        // send the message to the server
        send(client_socket, buffer, strlen(buffer), 0);
        printf("%s>", username);
    }

    close(client_socket);
    
    return 0;
}