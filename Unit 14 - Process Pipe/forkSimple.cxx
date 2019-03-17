/*
 * forkSimple.cxx
 * 
 * 	Example Program for CSCI 330
 *  shows fork system call
 * 
 */
#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
	
	cout << "Before fork\n";
	
	fork();
	
	cout << "After fork\n";
	
	return 0;
}
