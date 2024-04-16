#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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

	if (cwd == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
		while (1)
	{
		printf("%s ~$ ", cwd);
		read = getline(&input, &input_size, stdin);
		if (read == -1)
		{
			printf("Error reading input.\n");
			free(input);
			return (1);
		}

		if (input[read - 1] == '\n')
			input[read - 1] = '\0';

		if (strcmp(input, "exit") == 0)
			break;
			
		token = strtok(input, " ");
		while (token != NULL)
			{
				pid_t pid = fork();
				if (pid == -1)
				{
					perror("fork error:");
					return (1);
				}
				else if (pid == 0)
				{
					char *argv[] = {"/bin/bash", "-c",token , NULL};
					if (execve(argv[0], argv, NULL) == -1)
					{
						perror("execve error:");
						free(input);
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
