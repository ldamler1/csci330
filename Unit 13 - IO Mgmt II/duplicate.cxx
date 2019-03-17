/*
 * duplicate.cxx
 * 
 * 	Example Program for CSCI 330
 *  implements switch of standard output
 *  to arbitrary file
 * 
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
	// open existing file, append to it, or create new file
	int fd = open("other.txt", O_WRONLY | O_APPEND | O_CREAT, 00666);
	if (fd == -1) {
		perror("duplicate open");
		exit(EXIT_FAILURE);
	}
	// close standard output
	close(1);
	// duplicate fd into 1
	if (dup(fd) == -1) {
		perror("duplicate dup");
		exit(EXIT_FAILURE);
	}
	// close file
	close(fd);
	
	// write to file
	char buffer[] = "one line to write";
	cout << buffer << endl;	

	cerr << "wrote " << sizeof(buffer) << " bytes to file\n";
	
	return 0;
}
	
