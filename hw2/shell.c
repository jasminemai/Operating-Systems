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
#include <string.h>
#include "shell.h"

// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could 
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};

// --------------------------------------------
// Implementation for each prototype below
// --------------------------------------------
// void parse( char* line, command_t* p_cmd );
// int execute( command_t* p_cmd );
// int find_fullpath( char* command_name, command_t* p_cmd );
// int is_builtin( command_t* p_cmd );
// int do_builtin( command_t* p_cmd );
// void cleanup( command_t* p_cmd );

void parse( char* line, command_t* p_cmd )
{
	//check for spaces????????
	if(strcmp(line, "") == 0)
	{
		p_cmd -> path = NULL;
		p_cmd -> argv = NULL;
		p_cmd -> argc = 0;
	}
	else
	{
		int count = 0;
		char* tokenizer = strtok(line, " ");
		char** token = malloc(50 * sizeof(char*));
		while(tokenizer != NULL)
		{
			token[count] = tokenizer;
			count++;
			tokenizer = strtok(NULL, " ");	
		}
		token[count + 1] = NULL;

		for(int i = 0; valid_builtin_commands[i] != NULL; i++)
		{
			//THIS COMPARISON WON'T WORK AT ALL I DON'T UNDERSTAND
			if(strcmp(token[0], valid_builtin_commands[i]) == 0)
			{
				p_cmd -> path = token[0];
				p_cmd -> argv = token;
				p_cmd -> argc = count;
			}
		}

		if(find_fullpath(token[0], p_cmd) == TRUE)
		{
			p_cmd -> path = NULL;
			p_cmd -> argv = NULL;
			p_cmd -> argc = -1;
		}
		else
		{
			p_cmd -> argv = token;
			p_cmd -> argc = count;
		}
	}
}

int execute( command_t* p_cmd )
{
	int status;
	char fullpath[1000];
	if(p_cmd->argc > 0)
	{
		if(fork() == 0)
		{
			find_fullpath(fullpath, p_cmd);
			execv(fullpath, p_cmd->argv);
			exit(1);
		}
		wait(&status);
	}
	else if (p_cmd -> argc == -1)
	{
		perror("User command is not found");
	}
	return wait(&status);
}

int find_fullpath( char* command_name, command_t* p_cmd )
{
	char* path_env_variable;
	path_env_variable = getenv( "PATH" );
	//printf("PATH = %s\n", path_env_variable );
	char* path = strtok(path_env_variable, ":");

	char* file_or_dir = (char*) malloc(sizeof(char) * strlen(path_env_variable));
	p_cmd -> path = (char*) malloc(sizeof(char) * strlen(path_env_variable));
	//FREE YOUR MALLOC (free(file_or_dir))

	int boolean = 0;

	while(boolean == 0 && path != NULL)
	{
		struct stat buffer;
		int exists;
		strcpy(file_or_dir, path);
		strcat(file_or_dir, "/");
		strcat(file_or_dir, command_name);
		exists = stat(file_or_dir, &buffer);
		if (exists == 0)
		{
			p_cmd -> path = strcpy(p_cmd -> path, file_or_dir);
			boolean = 1;
			return TRUE;
		}
		path = strtok(NULL, ":");
		
	}
	if (boolean != 1)
	{
		p_cmd -> path = strcpy(p_cmd -> path, file_or_dir);
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

int is_builtin(command_t* p_cmd)
{
	for(int i = 0; valid_builtin_commands[i] != NULL; i++)
	{
		if(strcmp(p_cmd -> path, valid_builtin_commands[i]) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int do_builtin(command_t* p_cmd)
{
	if(strcmp(p_cmd -> path , valid_builtin_commands[0]) == 0)
	{
		return chdir(p_cmd->argv[1]);
	}
	else
	{
		return ERROR;
	}
	return SUCCESSFUL;
}

void cleanup( command_t* p_cmd )
{
 	free(p_cmd->path);
}