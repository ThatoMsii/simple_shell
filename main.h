#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void display_prompt(void);
void leo_print(const char *message);
void read_command(char *command, size_t size);
void execute_command(char *command);
#endif
