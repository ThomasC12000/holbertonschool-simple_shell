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
void env_builtin(void);
char *get_path(void);

#endif /* SHELL_H */
