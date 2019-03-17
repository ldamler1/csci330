/*
 * regex.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows regcomp and regexec library functions
 * 
 */
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {		
	// check for arguments
	if (argc < 3) {
		cerr << "Usage: regex text regex";
		exit(EXIT_FAILURE);
	}
	cout << "Search for: " << argv[2] << " in " << argv[1] << endl;
	
	regex_t regex;
	int rs;
	
	// prepare regular expression
	regcomp(&regex, argv[2], 0);
	
	// execute the regular expression
	rs = regexec(&regex, argv[1], 0, 0, 0);	
	if (rs == 0)
		cout << argv[1] << " is matched by: " << argv[2] << endl;
	else
		cout << "no match" << endl;
}
