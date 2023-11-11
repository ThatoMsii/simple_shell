#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include <stddef.h>
/**
 *main - all functions of the body are in the main.
 *environ - variable.
 *return - always 0 success.
 */

#define MAX_INPUT_LENGTH 1024
extern char **environ;

int main(int argc, char *argv[])
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			perror("fgets");
			exit(EXIT_FAILURE);
		}
		size_t input_length = strlen(input);

		if (input_length > 0 && input[input_length - 1] == '\n')
	{
		input[input_length - 1] = '\0';
	}
	if (strcmp(input, "env") == 0)
	{
		char **env = environ;

		while (*env != NULL)
		{
			write(STDOUT_FILENO, *env, strlen(*env));
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	} else if (strcmp(input, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	}
	return (0);
}
