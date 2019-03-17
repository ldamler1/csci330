/*
 * execSimple.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows exec switch to ps
 * 
 */
#include <unistd.h>
#include <sys/types.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
	
	int rs;
	
	cout << "program started in process: " << getpid() << endl;
	
	rs = execl("/bin/ps", "ps", (char *)NULL);
	if (rs == -1) {
		perror("execl");
		exit(rs);
	}
	cout << "Maybe we see this ?\n";
	
	return 0;
}
