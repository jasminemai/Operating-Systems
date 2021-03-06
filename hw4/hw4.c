#include <stdio.h>
#include "dpsim.h"

/**************************************************

Main Function:
	int main( int argc, char** argv )

------------------------------------------------
In this function perform the following steps:
------------------------------------------------
1. Create the following variables:
	- main_thread (pthread_t)
	- status (join status value)
2. Create a main_thread 
	- If the return value != 0, then display an error message and 
	  immediately exit program with status value 1.
3. Join the main_thread
	- If the return value != 0, then display an error message and
	  immediately exit the program with status value 2.
4. Display join status value.
5. Exit program.

*/
pthread_t main_thread;
int main( int argc, char** argv ) 
{
	int status;

	if (pthread_create(&main_thread, NULL, th_main, (void*)0) != 0)
	{
		status = 1;
		exit(1);
	}
	if(pthread_join(main_thread, NULL) != 0)
	{
		status = 2;
		exit(2);
	}
	printf("Status Value: %d\n", status);
	return 0;

} // end main function