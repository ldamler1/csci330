/*
 * forkLoopWait.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows fork and wait system calls
 * 
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
 
int main() {
   pid_t  pid;
   // fork will make 2 processes
   pid = fork();
   if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
 
   if (pid == 0) {
      // Child process: fork() returned 0
      for (int j = 0; j < 5; j++) {
		cout << "child: " << j << endl;
	  }
   } else { 
      // Parent pocess: fork() returned a positive number
      // wait for child to end
      wait(NULL);
      for (int i = 0; i < 5; i++) {
		cout << "parent: " << i << endl;
	  }
   }
   cout << "end of process:" << getpid() << endl;
   return 0;
}
