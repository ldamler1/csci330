/*
 * TCPServerFork.cxx
 * 
 * TCP echo server
 * 
 * 	loops/waits/forks for message received from client 
 * 	      send message back to client
 * 
 * 	command line arguments:
 * 		argv[1] port number to receive from
 * 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

void processClientRequest( int connSock) {
	int received;
	char buffer[1024];
	
	// read a message from the client
	if ((received = read(connSock, buffer, sizeof(buffer))) <= 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	
	cout << "Client sent " << received << " bytes: " << buffer << endl;
		
	// write the message back to client 
	if (write(connSock, buffer, received) < 0) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(connSock);
	exit(EXIT_SUCCESS);
}
        
int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << "USAGE: TCPServerFork port\n";
		exit(EXIT_FAILURE);
	}
	
	// Create the TCP socket 
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}	
	// create address structures
	struct sockaddr_in server_address;  // structure for address of server
	struct sockaddr_in client_address;  // structure for address of client
	unsigned int addrlen = sizeof(client_address);	

	// Construct the server sockaddr_in structure 
	memset(&server_address, 0, sizeof(server_address));   /* Clear struct */
	server_address.sin_family = AF_INET;                  /* Internet/IP */
	server_address.sin_addr.s_addr = INADDR_ANY;          /* Any IP address */
	server_address.sin_port = htons(atoi(argv[1]));       /* server port */

	// Bind the socket
	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}	
	
	// listen: make socket passive and set length of queue
	if (listen(sock, 64) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	cout << "TCPServer listening on port: " << argv[1] << endl;
	
	// Run until cancelled 
	while (true) {
		int connSock=accept(sock, (struct sockaddr *) &client_address, &addrlen);
		if (connSock < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		// fork
		if (fork()) { 	    // parent process
			close(connSock);
		} else { 			// child process
			processClientRequest(connSock);
		}
	}	
	close(sock);
	return 0;
}
