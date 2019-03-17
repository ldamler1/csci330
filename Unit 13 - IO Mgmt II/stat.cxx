/*
 * stat.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows stat system call
 * 
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {	
	// check command line agruments
	if (argc < 2) {
		cerr << "Usage: stat filename\n";
		exit(EXIT_FAILURE);
	}	
	int rs;
	struct stat buffer;
	// call stat system call
	rs = stat(argv[1], &buffer);
	if (rs == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	// print results
	cout << "status report: " << argv[1] << endl;
	cout << "... size: " << buffer.st_size << endl;
	cout << "... owner: " << buffer.st_uid << endl;	
	if (S_IRUSR & buffer.st_mode) cout << "... owner can read\n";
	if (S_ISREG(buffer.st_mode))  cout << "... is a file\n";	
	if (S_ISDIR(buffer.st_mode))  cout << "... is a directory\n";
	return 0;
}
