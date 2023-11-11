#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - entry point
 * fgets - read user input
 * strtok - tokenizes a string
 * strcmp - checks if two strings are ==
 * execvp - replaces the current process
 * wait - causes the parent process to wait
 * perror - prints an error message
 * return - Always 0, success
 */
#define MAX_COMMAND_LENGTH 100

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[10];
	int numArgs;

	while (1)
	{
		printf("SimpleShell> ");
		fgets(command, MAX_COMMAND_LENGTH, stdin);

		command[strcspn(command, "\n")] = '\0';

		char *token = strtok(command, " ");

		numArgs = 0;

		while (token != NULL)
		{
			args[numArgs] = token;
			token = strtok(NULL, " ");
			numArgs++;
		}
		if (numArgs == 0)
		{
			continue;
		}
		args[numArgs] = NULL;
		if (strcmp(args[0], "exit") == 0)
		{
			printf("Exiting the shell\n");
			exit(0);
		}
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
		} else if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Command execution failed");
				exit(1);
			}
		} else
		{
			wait(NULL);
		}
	}
	return (0);
}
