/*
 * readDir.cxx
 * 
 * sample program to list directory content 
 * 	      
 */
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {	
	if (argc != 2) {
		cerr << "USAGE: readDir pathname\n";
		exit(EXIT_FAILURE);
	}
	
	DIR *dirp;
	struct dirent *dirEntry;
	
	// open directory
	dirp = opendir(argv[1]);
	if (dirp == 0) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
		
	while ((dirEntry = readdir(dirp)) != NULL) {		
		cout << dirEntry->d_name << endl;		
	}	
	
	closedir(dirp);
	return 0;
}
