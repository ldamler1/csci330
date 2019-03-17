/*
 * pipeSimple.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows pipe system call
 * 
 */

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
	
	cout << "Before pipe\n";
	
	int pipefd[2], rs;
	
	rs=pipe(pipefd);
	if (rs == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	write(pipefd[1],"Hello", 6);
	
	char buffer[256];
	read(pipefd[0], buffer, sizeof(buffer));
	
	cout << "pipe contained: " << buffer << endl;
	
	return 0;
}
