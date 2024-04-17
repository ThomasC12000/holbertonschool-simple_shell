#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: An array containing the command line arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *token;
	char *cwd = getenv("PWD");
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read;
	pid_t pid;

	if (cwd == NULL)
	{
		perror("getcwd() error");
		return (1);
	}

	if (!isatty(fileno(stdin)))
	{
		read = getline(&input, &input_size, stdin);
		if (read == -1)
		{
			printf("Error reading input.\n");
			free(input);
			return (1);
		}

		input[strcspn(input, "\n")] = '\0';

		token = strtok(input, " ");
		while (token != NULL)
		{
			if (access(token, X_OK) == -1)
			{
				printf("Command not found: %s\n", token);
				break;
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork error:");
				return (1);
			}
			else if (pid == 0)
			{
				char **cmd_argv = malloc(sizeof(char *) * 4);

				if (cmd_argv == NULL)
				{
					perror("malloc error:");
					free(input);
					return (1);
				}
				cmd_argv[0] = "/bin/bash";
				cmd_argv[1] = "-c";
				cmd_argv[2] = token;
				cmd_argv[3] = NULL;

				if (execve(cmd_argv[0], cmd_argv, NULL) == -1)
				{
					perror("execve error:");
					free(input);
					free(cmd_argv);
					return (1);
				}
				exit(0);
			}
			else
			{
				int status;
				
				waitpid(pid, &status, 0);
			}
			token = strtok(NULL, " ");
		}
		free(input);
		return (0);
	}

	while (1)
	{
		printf("%s ~$ ", cwd);
	read = getline(&input, &input_size, stdin);
	if (read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			break;
		}
		printf("Error reading input.\n");
		free(input);
		return (1);
	}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		token = strtok(input, " ");
		while (token != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork error:");
				return (1);
			}
			else if (pid == 0)
			{
				char **cmd_argv = malloc(sizeof(char *) * 4);

				if (cmd_argv == NULL)
				{
					perror("malloc error:");
					free(input);
					return (1);
				}
				cmd_argv[0] = "/bin/bash";
				cmd_argv[1] = "-c";
				cmd_argv[2] = token;
				cmd_argv[3] = NULL;

				if (execve(cmd_argv[0], cmd_argv, NULL) == -1)
				{
					perror("execve error:");
					free(input);
					free(cmd_argv);
					return (1);
				}
				exit(0);
			}
			else
			{
				int status;

				waitpid(pid, &status, 0);
			}
			token = strtok(NULL, " ");
		}
	}
	(void)argc;
	(void)argv;
	free(input);
	return (0);
}
