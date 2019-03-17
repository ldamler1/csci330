/*
 * readAll.cxx
 * 
 *  implements simple read from file:
 * 		- filename specified as commmand line argument 
 * 		- reads complete file content
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

int main(int argc, char* argv[]) {
	int fd, count, sum=0;
	// check command line arguments
	if (argc < 2) {
		cerr << "Usage: readAll filename\n";
		exit(EXIT_FAILURE);
	}
	char buffer[1024];
	// open file
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	// read from file
	while ((count = read(fd, buffer, 1024)) != 0) {
		if (count == -1) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		sum += count;	
		cout << "read " << count << " bytes from file\n";
	}
	cout << "read all " << sum << " bytes from " << argv[1] << endl;
	// close  file
	close(fd);
	return 0;
}
	
