// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <string.h> //MAKE SURE WE CAN USE THIS
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//				argv = array of argument values
//
//
int main( int argc, char** argv ) 
{

	// ----------------------------------
	// Pseudocode
	// ----------------------------------
	// while ( !done )
	//		print the prompt (i.e. >, #, or $ ... your choice)
	//		read command line
	//		parse the command line
    //      if (parsed command is "exit")
    //      	done = true
	//  	else if ( is _builtin( ... ) )
	//			do_builtin( ... )
	//		else if ( found in path )
	//  		execute( ... )
	//		else
	//			error()
	// 		cleanup( ... )
	//
	command_t cmd;
	int done = 0;
	char userInput[1000];
	while(done == 0)
	{
		printf("<3 ");
		//scanf("%s", userInput);
		fgets(userInput, 1000, stdin);
		parse(userInput, &cmd);
		if(strcmp(userInput, "exit\n") == 0)
		{
			done = 1;
		}
		else if (is_builtin(&cmd) == TRUE)
		{
			do_builtin(&cmd);
		}
		else if (find_fullpath(userInput, &cmd) == TRUE)
		{
			execute(&cmd);
		}
		else if(userInput[0] == '\n')
		{

		}
		else
		{
			perror("Try again ^-^");
		}
		//printf("\n");
	}
	cleanup(&cmd);
	return 0;

} // end main function
