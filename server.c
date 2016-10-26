
// -----------------------------------
// Jasmine Mai
// CSCI 340 - Operating Systems
// Fall 2016
// server.h header file
// Homework 1
//
// -----------------------------------

#include <string.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include <stdlib.h>

// ------------------------------------
// Function prototype that creates a socket and 
// then binds it to the specified port_number 
// for incoming client connections
// 
//
// Arguments:	port_number = port number the server 
//				socket will be bound to.
//
// Return:      Socket file descriptor (or -1 on failure)
//

int bind_port( unsigned int port_number ) {

	// -------------------------------------
	// NOTHING TODO HERE :)
	// -------------------------------------
	// Please do not modify

	int socket_fd;
	int set_option = 1;

	struct sockaddr_in server_address;

	socket_fd = socket( AF_INET, SOCK_STREAM, 0 );

	setsockopt( socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&set_option, sizeof( set_option ) );

	if (socket_fd < 0) return FAIL;

	bzero( (char *) &server_address, sizeof(server_address) );

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons( port_number );

	if ( bind( socket_fd, (struct sockaddr *) &server_address, sizeof(server_address) ) == 0 ) {

		return socket_fd;

	} else {

		return FAIL;

	}

} // end bind_port function

// ------------------------------------
// Function prototype that accepts a client
// socket connection
// 
//
// Arguments:	server file descriptor
//
// Return:      Termination status of client
//				( 0 = No Errors, -1 = Error )
//
int accept_client( int server_socket_fd ) {

	int exit_status = OK;

	int client_socket_fd = -1;

	socklen_t client_length; 

	struct sockaddr_in client_address;

	char request[512];


	client_length = sizeof( client_address );

	client_socket_fd = accept( server_socket_fd, (struct sockaddr *) &client_address, &client_length );

	//Forking a child process
	if(fork() == 0)
	{
		if ( client_socket_fd >= 0 ) {

		//fork here :)

			bzero( request, 512 );

			read( client_socket_fd, request, 511 );

			if ( DEBUG ) printf("Here is the http message:\n%s\n\n", request );

		/*
		 ------------------------------------------------------
		 GET method key/values are located in the URL of the request message
		 ? - indicates the beginning of the key/value pairs in the URL
		 & - is used to separate multiple key/value pairs 
		 = - is used to separate the key and value
		 
		 Example:
		 
		 http://localhost/?first=brent&last=munsell
		 
		 two &'s indicated two key/value pairs (first=brent and last=munsell)
		 key = first, value = brent
		 key = last, value = munsell
		 ------------------------------------------------------
		 */

		 char response[512];

		 char* requestDuplicate = strdup(request);
		 if(strcmp(strtok(requestDuplicate," "), "GET") == 0)
		 {
		 	char* stringValues = (strtok(NULL, " "));
		 	char* modifiedString = stringValues+=2;
		 	char* stringTokens = strtok (modifiedString,"&=");
		 	int count = 0;
		 	char get_entity[] = "<html><body><body><h2>CSIS 340 (Advanced Operating Systems) Project 1</h2><table border=1 width=\"50%\"><tr><th>Key</th><th>Value</th></tr>";
		 	while(stringTokens != NULL)
		 	{
		 		if(count%2 == 0)
		 		{
					//sprintf here maybe?
		 			strcat(get_entity, "<tr><td><b>");
		 			strcat(get_entity,stringTokens);
		 			strcat(get_entity,"</b></td>");
		 			stringTokens = strtok (NULL, "&=");

		 		}
		 		else
		 		{
		 			strcat(get_entity, "<td>");
		 			strcat(get_entity, stringTokens);
		 			strcat(get_entity, "</td>");
		 			stringTokens = strtok (NULL, "&=");
		 			strcat(get_entity, "</tr>");
		 		}
		 		count++;
		 	}
		 	strcat(get_entity, "</table></body></html>");
		 	sprintf( response, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s", (int)strlen( get_entity ), get_entity );
		 }

		 /*
		 ------------------------------------------------------
		 POST method key/value pairs are located in the entity body of the request message
		 ? - indicates the beginning of the key/value pairs
		 & - is used to delimit multiple key/value pairs 
		 = - is used to delimit key and value
		 
		 Example:
		 
		 first=brent&last=munsell
		 
		 two &'s indicated two key/value pairs (first=brent and last=munsell)
		 key = first, value = brent
		 key = last, value = munsell
		 ------------------------------------------------------
		 */
		 if(strcmp(strtok(requestDuplicate," "), "POST") == 0)
		 {
		 	char post_entity[] = "<html><body><body><h2>CSIS 340 (Advanced Operating Systems) Project 1</h2><table border=1 width=\"50%\"><tr><th>Key</th><th>Value</th></tr>";
		 	char* postTokens = (strtok(request, "\n"));
		 	printf("%s\n", postTokens );
		 	int boolean = 0;
		 	while(boolean == 0)
		 	{
		 		postTokens = strtok(NULL, "\n");
		 		if (strlen(postTokens) == 1)
		 		{
		 			postTokens = strtok(NULL, "\n");
		 			boolean = 1;
		 		}
		 	}

		 	postTokens = strtok (postTokens,"&=");
		 	int count = 0;

		 	while(postTokens != NULL)
		 	{
		 		if(count%2 == 0)
		 		{
		 			strcat(post_entity, "<tr><td><b>");
		 			strcat(post_entity,postTokens);
		 			strcat(post_entity,"</b></td>");
		 			postTokens = strtok (NULL, "&=");

		 		}
		 		else
		 		{
		 			strcat(post_entity, "<td>");
		 			strcat(post_entity, postTokens);
		 			strcat(post_entity, "</td>");
		 			postTokens = strtok (NULL, "&=");
		 			strcat(post_entity, "</tr>");
		 		}
		 		count++;
		 	}
		 	strcat(post_entity, "</table></body></HTML>");
		 	//char response[512];
		 	sprintf( response, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s", (int)strlen( post_entity ), post_entity );

		 }

		 if ( DEBUG ) printf( "%s\n", response );



		 write( client_socket_fd, response, strlen( response ) );
		 close( client_socket_fd );

		}
		else  {

			exit_status = FAIL;


		}

		if ( DEBUG ) printf("Exit status = %d\n", exit_status );
		exit(0);
	} // end of fork 
	else{
		close( client_socket_fd );
	}

	return exit_status;
	} // end accept_client function