/*
 * ForkRunCommand.cxx
 * 
 * 	Example Program for CSCI 330
 *  prompts for command to run in forked process
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
	
   string command, argument;
   // prompt user for command to run
   cout << "Enter command to run (with one argument): ";
   cin >> command >> argument;
   
   int pid, rs, status;
   // fork will make 2 processes
   pid = fork();
   if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
 
   if (pid == 0) {
      // Child process: exec to command with argument
      cout << "before exec to: " << command << " " << argument << endl;
      
      rs = execlp(command.c_str(), command.c_str(), argument.c_str(), (char*) NULL);
      
      if (rs == -1) { perror("execlp"); exit(EXIT_FAILURE); }
   } else { 
      // Parent process: wait for child to end
      wait(&status);
   }
   cout << "end of process: " << getpid() << endl;
   return 0;
}
