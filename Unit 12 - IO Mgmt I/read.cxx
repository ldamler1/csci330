/*
 * read.cxx
 * 
 * 	Example Program for CSCI 330
 *  implements simple read from file
 *  via open/read/close system calls
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
	int fd, count;
	char buffer[1024], filename[] = "example.txt";
	// open file
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror(filename);
		exit(EXIT_FAILURE);
	}
	// read from file
	count = read(fd, buffer, 1024);
	if (count == -1) {
		perror(filename);
		exit(EXIT_FAILURE);
	}	
	cout << "read " << count << " bytes from file\n";
	// close  file
	close(fd);
	return 0;
}
	
