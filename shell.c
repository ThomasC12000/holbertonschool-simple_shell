#include "shell.h"

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

/**
 * main - Entry point for the shell program
 * Return: Always 0
 */
int main(void)
{
	char *command = NULL;
	size_t command_size = 0;
	ssize_t bytes_read;
	char *args[MAX_ARGS], *token;
	int should_run = 1, i;

	while (should_run)
	{
		if (isatty(STDIN_FILENO))
			printf("\033[32m@%s\033[0m ➜ \033[36m%s\033[0m $ ",
				_getenv("USER"),	_getenv("PWD"));
		fflush(stdout);
		bytes_read = getline(&command, &command_size, stdin);
		if (bytes_read == -1)
			break;
		while (*command == ' ' || *command == '\t')
            command++;

         if (*command == '\0' || *command == '\n')
            continue;

        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0)
        {
            should_run = 0;
            continue;
        }
        if (strcmp(args[0], "env") == 0)
		{
			env_builtin();
			continue;
		}
		i = 0;
		token = strtok(command, " ");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		execute_command(args);
	}
	free(command);
	return (0);
}

