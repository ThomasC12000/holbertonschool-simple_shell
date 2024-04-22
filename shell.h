#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int execute_command(char *args[]);
char *find_executable(char *command);
char *_getenv(const char *name);

#endif /* SHELL_H */
