/*
 * write.cxx
 * 
 * 	Example Program for CSCI 330
 *  implements simple write to existing file
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
	char buffer[] = "one line to write";
	// open existing file, will overwrite current content
	fd = open("example.txt", O_WRONLY);
	if (fd == -1) {
		perror("example.txt");
		exit(fd);
	}
	// write to file
	count = write(fd, buffer, sizeof(buffer));	
	if (fd == -1) {
		perror("example.txt");
		exit(fd);
	}
	cout << "wrote " << count << " bytes to file\n";
	// close file
	close(fd);
	return 0;
}
	
