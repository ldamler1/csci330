/*
 * unlink.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows unlink system call
 * 
 */
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	// check command line agruments
	if (argc < 2) {
		cerr << "Usage: unlink filename\n";
		exit(EXIT_FAILURE);
	}
	
	int rs;
	rs = unlink(argv[1]);
	if (rs == -1) {
		perror(argv[1]);
		exit(rs);
	}
	
	return 0;
}
