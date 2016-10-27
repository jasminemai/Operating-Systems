// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


int file_path( char* full_path, char* cmd );
int file_exists( char* full_path );


// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//				argv = array of argument values
//
//
int main( int argc, char** argv ) {

	
	char* cmd = argv[1];
	char full_path[50];

	int error;
	int child_process_status;

	pid_t child_pid;
	pid_t pid;
	
	char* args[] = { argv[1], NULL };

	error = file_path( full_path, cmd );

	if ( !error ) {

		printf("***************************\n");
		printf("Found executable file [%s]\n", full_path );
		printf("***************************\n");

		child_pid = fork();

		if ( child_pid == 0 ) {

			printf("Hi!");
			execv( full_path, args );
			perror( "fork child process error condition!" );

		}

		pid = wait( &child_process_status );

		printf("--------------------------\n");
		printf("Parent(%d), Child(%d) w/ exit PID(%d)\n", getpid(), child_pid, pid );
		printf("--------------------------\n");

	} else {

		printf("command %s is not in your path!\n", cmd );

	}

	return 0;

} // end main function


int file_path( char* full_path, char* cmd ) {

	char* path = getenv( "PATH" );

	int i = 0;
	int j = 0;
	int k = 0;
	int error = 1;

	while ( path[i] != '\0' ) {

		if ( path[i] != ':' ) { 

			full_path[j++] = path[i];

		} else {

			full_path[j++] = '/';

			while ( cmd[k] != '\0') {

				full_path[j++] = cmd[k++];

			}

			full_path[j] = '\0';

			j=0;
			k=0;

			if ( file_exists( full_path ) ) {

				error = 0;
				break;

			}

		}

		i++;

	}

	return error;

}


int file_exists( char* full_path ) {

	struct stat buff;
	
	int exists;
	
	exists = stat( full_path, &buff );

	return ( exists == 0 && ( S_IFREG & buff.st_mode ) ) ? 1 : 0;

}


