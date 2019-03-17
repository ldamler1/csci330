/*
 * pipeFork.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows pipe and fork system calls
 * 
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
	
	int pipefd[2], rs;
	char buffer[256];
	
	// create pipe
	rs = pipe(pipefd);
	if (rs == -1) { perror("pipe"); exit(EXIT_FAILURE); }
	cout << "pipe created\n";
	
	// fork into 2 processes
	rs = fork();
	if (rs == -1) { perror("fork"); exit(EXIT_FAILURE); }
	
	if (rs == 0) { // child process	
		// close write end of pipe
		close(pipefd[1]);
		// read from read end of pipe
		read(pipefd[0], buffer, sizeof(buffer));
		cout << "pipe contained: " << buffer << endl;			
	} else {  // parent process	
		// close read end of pipe
		close(pipefd[0]);
		// write to write end of pipe
		write(pipefd[1],"Hello", 6);
		wait(NULL);	
	}	
	return 0;
}
