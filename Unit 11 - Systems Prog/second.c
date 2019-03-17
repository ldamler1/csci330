#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	int count = 1;
	
	printf("Welcome to the sample C++ program\n");
	
	// show all command line arguments
	for (int i=0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
 
	// if no argument was given, prompt the user
	if (argc == 1) {
		printf("Enter number to repeat: ");
		scanf("%d", &count);
	} else {
		count = atoi(argv[1]);
	}
	
	// show line a few times
	for (int i=0; i < count; i++)
		printf("C++ is fun !\n");
		
	return 0;
}
