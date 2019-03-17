/*
 * copy.cxx
 * 
 * 	Example Program for CSCI 330
 *  implement copy by reading file, and writing file
 *  via read/write system calls
 * 
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	int ifd, ofd, count, sum=0;
	char buffer[1024];
	
	// check command line arguments
	if (argc < 3) {
		cerr << "Usage: copy fromFile toFile\n";
		exit(EXIT_FAILURE);
	}
	// open file to read
	ifd = open(argv[1], O_RDONLY);
	if (ifd == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	// open file to write
	ofd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 00666);
	if (ofd == -1) {
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}
	// loop to read/write buffer
	while ((count = read(ifd, buffer, sizeof(buffer))) != 0) {
		if (count == -1) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		count = write(ofd, buffer, count);
		if (count == -1) {
			perror(argv[2]);
			exit(EXIT_FAILURE);
		}
		sum += count;
	}
	cout << "copied " << sum << " bytes from " << argv[1] << " to " << argv[2] << endl;
	// close all files
	close(ifd);
	close(ofd);
	return 0;
}
	
