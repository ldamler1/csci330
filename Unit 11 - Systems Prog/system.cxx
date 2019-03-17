/*
 * system.cxx
 * 
 * 	Example Program for CSCI 330
 *  demonstrates system and exit library functions
 * 
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main () {
  int rs;
  cout << "Checking if processor is available ...";
  if (system(NULL)) 
     cout << " Ok \n";
  else 
     exit (EXIT_FAILURE);
  cout << "Executing command ls -l ...\n";
  rs = system ("ls -l");
  return rs;
}
