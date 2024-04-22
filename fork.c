#include "shell.h"

#define MAX_PATH_LEN 1024

/**
 * is_path - checks if the command is a path
 * @command: command to check
 * Return: 1 if it is a path, 0 if not
 */
int is_path(char *command)
{
	int i = 0;

	if (command == NULL)
		return (0);

	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	};
	return (0);
}

/**
 * find_executable - Finds the full path of an executable file
 * @command: The command to search for
 *
 * Return: The full path of the executable file if found, otherwise NULL
 */
char *find_executable(char *command)
{
	char *path;
	char *token;
	char *full_path, *result;

	if (is_path(command))
		return strdup(command);

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Erreur: Impossible de récupérer le chemin\n");
		return (NULL);
	}

	full_path = malloc(MAX_PATH_LEN);
	if (full_path == NULL)
	{
		fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire\n");
		return (NULL);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, MAX_PATH_LEN, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			result = strdup(full_path);
			free(full_path);
			return (result);
		}
	token = strtok(NULL, ":");
	}
	free(full_path);
	return (NULL);
}

/**
 * execute_command - Execute a command with its arguments
 * @args: Array of strings containing the command and its arguments
 * Return: 0 on success, 1 on failure
 */

int execute_command(char *args[])
{
	pid_t pid;

	pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Erreur lors de la création du processus fils\n");
		return (1);
	}
	if (pid == 0)
	{
		char *full_path = find_executable(args[0]);

		if (full_path == NULL)
		{
			fprintf(stderr, "Erreur: commande introuvable\n");
			exit(EXIT_FAILURE);
		}

		if (execve(full_path, args, environ) == -1)
		{
			perror("Erreur lors de l'exécution de la commande");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
