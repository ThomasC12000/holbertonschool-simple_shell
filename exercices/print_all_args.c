#include <stdio.h>

/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: An array containing the command line arguments
 *
 * Return: 0 on success
 */


int main(int argc, char **argv)
{
	char input[100];

	printf("~$ ");

	if (fgets(input, sizeof(input), stdin) != NULL)
	{
		printf("Command entered: %s", input);
	}
	else
	{
		printf("Error reading input.\n");
		return (1);
	}
	(void)argv;
	(void)argc;
	return (0);
}
