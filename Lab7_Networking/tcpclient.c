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

    // Create a socket
	int client_socket;
	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
        return -1;
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002); 
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	int connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	// Report back to user if our connection was successful
	if(connection_status  <0 ){
		printf("%d Connection unsuccessful\n", connection_status);
		close(client_socket);
		return -1;	
	} else {
		printf("Connected successfully\n");
	}

    // Receive data from the server
	char server_response[256];
	recv(client_socket, &server_response, sizeof(server_response), 0);
	
	// Print out the server's response
	printf("The server sent the data: %s\n",server_response);

	// Then close the socket
	close(client_socket);

    return 0;
}