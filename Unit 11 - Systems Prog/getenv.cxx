/*
 * getenv.cxx
 * 
 * 	Example Program for CSCI 330
 *  demonstrates environment variable access library function
 * 
 */
#include <iostream>
#include <cstdlib>
using namespace std;

int main () {
  char * path;
  path = getenv ("PATH");
  if (path != NULL)
     cout << "The current path is: " << path << endl;
  return 0;
}
