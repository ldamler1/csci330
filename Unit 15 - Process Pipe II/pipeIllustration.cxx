/*
 * pipeIllustration.cxx
 * 
 * 	Example Program for CSCI 330
 *  	shows pipe, fork, dup and execlp system calls
 * 		parent process waits for children to end
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
		
	// create pipe
	int pipefd[2];
	int rs = pipe(pipefd);
	if (rs == -1) { perror("pipe"); exit(EXIT_FAILURE); }
	
	// fork into 2 processes
	rs = fork();
	if (rs == -1) { perror("fork"); exit(EXIT_FAILURE); }

	if (rs == 0) { // child process	1
			
		// close read end of pipe, keep write end open
		close(pipefd[0]);
		// close standard output
		close(1);
		// duplicate write end of pipe into standard output
		dup(pipefd[1]);
		// close write end of pipe
		close(pipefd[1]);		
		// run first command
		rs = execlp("ls", "ls", (char*)NULL);
		if (rs == -1) { perror("execlp"); exit(EXIT_FAILURE); }	
				
	} else {  // parent process	
	
		// close write end of pipe, keep read end open
		close(pipefd[1]);
		
		// fork into 2 processes
		rs = fork();
		if (rs == -1) { perror("fork"); exit(EXIT_FAILURE); }
		
		if (rs == 0) { // child process	2
			// close standard input
			close(0);
			// duplicate read end of pipe into standard input
			dup(pipefd[0]);
			// close read end of pipe
			close(pipefd[0]);
				
			// run second command
			rs = execlp("wc", "wc", (char*)NULL);
			if (rs == -1) { perror("execlp"); exit(EXIT_FAILURE); }
			
		} else { // parent process
		
			// close read end of pipe
			close(pipefd[0]);
			
			wait(NULL); // for first child
			wait(NULL); // for second child
			cout << "Parent done\n";
			
		}
	}
	return 0;
}
