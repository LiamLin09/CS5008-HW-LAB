// CS 5008 LAB 7 Networking
// Author: Nianlong Lin
// Date: 10/22/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

int main() {

	// create a server socket
    int server_socket;	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define the server address format
    struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

    // Binding the server
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("Server bind()\n");

    // listen for client connections
    listen(server_socket, 27);

    //accept connections to the server
    // Integer to hold a potential client socket
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// send a message from the server
	char server_message[256] = "You have reached the server";

	send(client_socket, server_message, sizeof(server_message), 0);

	// Close the socket
	close(server_socket);

    return 0;


}