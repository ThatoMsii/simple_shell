#include <unistd.h>

/**
 * main - Entry point
 *
 * Description: A simple C program that prints a message to the standard output
 *
 * Return: 0 (Success)
 */
int main(void)
{
	char *message = "Hello, Betty!\n";
	int len = 13;

	if (write(1, message, len) != len)
	{
		write(2, "Write error\n", 12);
		return (1);
	}
	return (0);
}
