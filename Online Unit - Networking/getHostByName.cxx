/*
 * getHostName.cxx
 * 
 * 	do DNS lookup
 * 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char*argv[]) {
	struct addrinfo *res;
	int error;
	const char *hostname = "faculty.cs.niu.edu";
	
	if (argc > 1) {
		hostname = argv[1];
	} 
		
	error = getaddrinfo(hostname, NULL, NULL, &res);
	if (error) {
		cerr << hostname << ": " << gai_strerror(error) << endl;
		exit(EXIT_FAILURE);
	}	
	
	// convert generic sockaddr to Internet sockaddr_in
	struct sockaddr_in *addr = (struct sockaddr_in *) res->ai_addr;
	// convert network representation into printable presentation
	cout << hostname << " is: " << inet_ntoa(addr->sin_addr) << endl;
}
