/*
 * strcpy.cxx
 * 
 * 	Example Program for CSCI 330
 *  demonstrates string copy library function
 * 
 */
#include <cstring>
#include <iostream>
using namespace std;

int main () {
  char str1[]="Sample string";
  char str2[20];
  char str3[20];
  strcpy (str2,str1);
  strcpy (str3,"copy successful");
  cout << "str1: " << str1 << endl;
  cout << "str2: " << str2 << endl;
  cout << "str3: " << str3 << endl;
  return 0;
}
