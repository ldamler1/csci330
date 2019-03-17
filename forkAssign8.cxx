/*
 * z1761739.cxx
 * 
 *  CSCI330 assign8
 *  Uses fork(), exec(), and wait() to interpret unix commands
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() 
	{
    char buffer[4096];

	cout << "Enter command: ";
	
	//used to get string input from user for commands
    while (fgets(buffer, sizeof(buffer), stdin))
    {	
		//exits is "exit" is entered
		if (strcmp(buffer, "exit\n") == 0)
			{
			cout << "end of process: " << getpid() << endl;
            exit(EXIT_SUCCESS);
			}
		
		//the following is used to seperate the char array into a indivual parts in a pointer to a char array
        char *argv[5];
        char **next = argv;
        char *temp = strtok(buffer, " \n");
        while (temp != NULL)
        {
            *next++ = temp;
            temp = strtok(NULL, " \n");
        }
        *next = NULL;
            
		int pid, rs, status;
		
		pid = fork();
		
		if(pid == -1){perror("fork"); exit(EXIT_FAILURE);}
		
		if(pid == 0)
			{
			rs = execvp(argv[0], argv);
			
			if(rs == -1){perror(argv[0]); exit(EXIT_FAILURE);}
			}
		else
			{
			//executes when child is finished
			wait(&status);
			cout << "Enter command: ";
			}
			
    }

    return 0;
	}
