#include "shell.h"

#define MAX_ENV_LEN 100

/**
 * _getenv - Gets the value of the specified environment variable
 * @name: The name of the environment variable to search for
 *
 * Return: The value of the environment variable if found, otherwise NULL
 */
char *_getenv(const char *name)
{
	char *env;
	int i, j;

	if (name == NULL) {
		return (NULL);
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		env = environ[i];
		j = 0;
		while (name[j] != '\0' && env[j] == name[j])
		{
			j++;
		}
		if (name[j] == '\0' && env[j] == '=')
		{
			return (env + j + 1);
		}
	}
	return (NULL);
}
