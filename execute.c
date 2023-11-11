#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
/**
 * main - Entry point
 *execute_command - function to take a single args.
 *
 *return - Always 0 success.
 */

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void execute_command(char *command)
{
	char *args[MAX_ARGS];
	int i = 0;
	char *token = strtok(command, " ");

	while (token != NULL && i < MAX_ARGS)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;

	if (i > 0)
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(1);
		} else if (pid > 0)
		{
			int status;

			waitpid(pid, &status, 0);
		} else
		{
			perror("fork");
		}
	}
}
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *prompt = ":) ";

	while (1)
	{
		write(1, prompt, strlen(prompt));
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			break;
		}
	}
	return (0);
}
