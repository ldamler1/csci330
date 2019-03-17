/*
 * forkWait.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows fork and wait system calls
 * 
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {	
	int pid, status;
	
	cout << "Before fork\n";
	
	fork();
	
	pid = wait(&status);	
	if (pid == -1) {
		cout << "nothing to wait for\n";
		return 255;
	} else
		cout << "done waiting for: " << pid << ", ended with: " << WEXITSTATUS(status) << endl;
		
	cout << "After fork\n";
	
	return 0;
}
