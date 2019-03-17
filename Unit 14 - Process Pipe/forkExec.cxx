/*
 * forkExec.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows fork and exec system calls
 * 
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	
	int rs, pid, status;
	
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(pid);
	}
	if (pid == 0) { //child process
		rs = execvp("echo", argv);
		if (rs == -1) {
			perror("execvp");
			exit(rs);
		}
	} else {	// parent process
		cout << "done waiting for: " << wait(&status) << endl;
	}
	
	return 0;
}
