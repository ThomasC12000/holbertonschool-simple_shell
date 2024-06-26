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
	int should_run = 1, i, is_empty;

	while (should_run)
	{
		is_empty = 1;

		if (isatty(STDIN_FILENO))
			printf("\033[32m@%s\033[0m ➜ \033[36m%s\033[0m $ ",
				_getenv("USER"), _getenv("PWD"));
		fflush(stdout);

		bytes_read = getline(&command, &command_size, stdin);
		if (bytes_read == -1)
		{
			break;
		}
		for (i = 0; i < bytes_read; i++) 
		{
			if (command[i] != ' ' && command[i] != '\t' && command[i] != '\n')
			{
				is_empty = 0;
				break;
			}
		}
		if (is_empty)
		{
			continue;
		}

		command[strlen(command) - 1] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			should_run = 0;
			continue;
		}
		if (strcmp(command, "env") == 0)
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
		args[i] = NULL;
		
		execute_command(args);
	}
	free(command);
	return 0;
}
