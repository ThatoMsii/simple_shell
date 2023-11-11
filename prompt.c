#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_COMMAND_LENGTH 100
/**
 * main - start point
 *
 * execute_command - separate function to handle command execution
 * command - stores the user's input
 * return - Always 0, success
 */
void execute_command(char *command);

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		char prompt[] = "#cisfun$ ";

		write(fileno(stdout), prompt, strlen(prompt));

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			write(fileno(stdout), "\n", 1);
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) == 0)
		{
			continue;
		}
		execute_command(command);
	}
	return (0);
}
void execute_command(char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (child_pid == 0)
	{
		char *args[] = {command, NULL};

		execve(command, args, NULL);
		char exec_error[] = "execve error\n";

		write(fileno(stdout), exec_error, strlen(exec_error));
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}
