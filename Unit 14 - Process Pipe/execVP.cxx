/*
 * execVP.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows exec switch to ls
 * 
 */
#include <unistd.h>
#include <sys/types.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	
	int rs;
	
	cout << "program started in process: " << getpid() << endl;
	
	rs = execvp("ls", argv);
	if (rs == -1) {
		perror("execvp");
		exit(rs);
	}
	cout << "Maybe we see this ?\n";
	
	return 0;
}
