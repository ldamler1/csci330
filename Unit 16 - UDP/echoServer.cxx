/*
 * echoServer.cxx
 * 
 * UPD echo server
 * 
 * 	loops/waits for message received from client 
 * 	      send message back to client
 * 
 * 	command line arguments:
 * 		argv[1] port number to receive from
 * 
 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
        
int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << "USAGE: echoServer port\n";
		exit(EXIT_FAILURE);
	}
	
	char buffer[256];
	int received = 0;
	
	int sock;
	struct sockaddr_in server_address;  // structure for address of server
	struct sockaddr_in client_address;  // structure for address of client
	unsigned int addrlen = sizeof(client_address);
	
	// Create the UDP socket 
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	// Construct the server sockaddr_in structure 
	memset(&server_address, 0, sizeof(server_address));    /* Clear struct */
	server_address.sin_family = AF_INET;                   /* Internet/IP */
	server_address.sin_addr.s_addr = INADDR_ANY;           /* Any IP address */
	server_address.sin_port = htons(atoi(argv[1]));        /* server port */

	// Bind the socket
	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	cout << "echoServer listening on port: " << argv[1] << endl;
	
	// Run until cancelled 
	while (true) {
		// Receive a message from the client
		if ((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &client_address, &addrlen)) < 0) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		cout << "Client (" << inet_ntoa(client_address.sin_addr) << ") sent " << received << " bytes: " << buffer << endl;
		// Send the message back to client 
		if (sendto(sock, buffer, received, 0, (struct sockaddr *) &client_address, addrlen) < 0) {
			perror("sendto");
			exit(EXIT_FAILURE);
		}
	}
	
	close(sock);
	return 0;
}
