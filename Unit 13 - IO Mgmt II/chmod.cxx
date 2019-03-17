/*
 * chmod.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows chmod system call
 * 
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// function to print permissions in ls-l style
void printPerms(mode_t st_mode) {
	cout << ((st_mode & S_IRUSR) ? "r" : "-");
	cout << ((st_mode & S_IWUSR) ? "w" : "-");
    cout << ((st_mode & S_IXUSR) ? "x" : "-");
    cout << ((st_mode & S_IRGRP) ? "r" : "-");
    cout << ((st_mode & S_IWGRP) ? "w" : "-");
    cout << ((st_mode & S_IXGRP) ? "x" : "-");
    cout << ((st_mode & S_IROTH) ? "r" : "-");
    cout << ((st_mode & S_IWOTH) ? "w" : "-");
    cout << ((st_mode & S_IXOTH) ? "x" : "-");
}

// function to ensure answer is Octal number
bool check(string answer) {
	if (answer.length() != 4) return false;
	if (answer[0] < '0' || answer[0] > '7') return false;
	if (answer[1] < '0' || answer[1] > '7') return false;
	if (answer[2] < '0' || answer[2] > '7') return false;
	if (answer[3] < '0' || answer[3] > '7') return false;
	return true;
}

// function to convert octal number into bits
int convert(string answer) {
	int conv = 0;
	for (int i=0; i<4; i++) {
		int value = answer[i] - '0';
		conv += (value * pow(8,3-i));
	}
	cout << answer << " converted to: " << conv << " as octal: " << oct << conv << endl;
	return conv;
}

int main(int argc, char* argv[]) {	
	// check command line agruments
	if (argc < 2) {
		cerr << "Usage: chmod filename\n";
		exit(EXIT_FAILURE);
	}	
	int rs;
	struct stat buffer;	
	// retrieve stat structure for file
	rs = stat(argv[1], &buffer);
	if (rs == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	cout << "Current permission for " << argv[1] << ": ";
	printPerms(buffer.st_mode);
	cout << endl;
	// ask user for new permission settings
	string answer;	
	cout << "Enter new permission mode (octal) for " << argv[1] << ": ";
	cin >> answer;
	if (!check(answer)) {
		cout << "Error: must be 4 digit octal number\n";
	} else {
		// changing permissions
		rs = chmod(argv[1], convert(answer));
		if (rs == -1) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		rs = stat(argv[1], &buffer);
		if (rs == -1) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		cout << "Current permission for " << argv[1] << ": ";
		printPerms(buffer.st_mode);
		cout << endl;
	}
	return 0;
}
