/*
 * echoClient.cxx
 * 
 * UPD echo client
 * 
 * 	sends message to echo server
 * 	waits for message received from server 
 * 	      
 * 	command line arguments:
 * 		argv[1] IP number of server
 * 		argv[2] port number to send to
 * 		argv[3] message to send
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
	
	if (argc != 4) {
		cerr << "USAGE: echoClient server_ip port message\n";
		exit(EXIT_FAILURE);
	}
	
	char buffer[256];
	int echolen, received = 0;
	
	int sock;
	struct sockaddr_in server_address;  // structure for address of server
	unsigned int addrlen = sizeof(server_address);
	
	// Create the UDP socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}
	
	// Construct the server sockaddr_in structure
	memset(&server_address, 0, sizeof(server_address));    /* Clear struct */
	server_address.sin_family = AF_INET;                   /* Internet/IP */
	server_address.sin_addr.s_addr = inet_addr(argv[1]);   /* IP address */
	server_address.sin_port = htons(atoi(argv[2]));        /* server port */
	
	// Send the message to the server (don't forget to count the terminating null)
	echolen = strlen(argv[3]) + 1;
	if (sendto(sock, argv[3], echolen, 0, (struct sockaddr *) &server_address, sizeof(server_address)) != echolen) {
		perror("sendto");
		exit(EXIT_FAILURE);
	}
	
	// Receive the message back from the server 
	if ((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &server_address, &addrlen)) != echolen) {
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}
	
	cout << "Server (" << inet_ntoa(server_address.sin_addr) << ") echoed: " << received << " bytes: " << buffer << endl;
	
	close(sock);
	return 0;
}
           
