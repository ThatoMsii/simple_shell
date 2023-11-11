#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_INPUT_SIZE 1024
/**
 * parse_command - parse the user's input into command arguments.
 * main - entry point
 * free_args - free memory for arguments's command
 * run_shell - function to exercute the shell itself
 */
void parse_command(char *input, char **args, int *arg_count)
{
	*arg_count = 0;
	char *token = strtok(input, " \t\n");

	while (token != NULL)
	{
		args[(*arg_count)++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	args[*arg_count] = NULL;
}

void free_args(char **args, int arg_count)
{
	for (int i = 0; i < arg_count; i++)
	{
		free(args[i]);
	}
}
void run_shell(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE];
	int arg_count;

	while (1)
	{
		printf("SimpleShell > ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break;
		}
		parse_command(input, args, &arg_count);

		if (arg_count == 0)
		{
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			break;
		}
		pid_t pid = fork();

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Exec error");
			}
			exit(EXIT_FAILURE);
		} else if (pid > 0)
		{
			int status;

			waitpid(pid, &status, 0);
		} else
		{
			perror("Fork error");
		}
		free_args(args, arg_count);
	}
}
int main(void)
{
	run_shell();
	return (0);
}
