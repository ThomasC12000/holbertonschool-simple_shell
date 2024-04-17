#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: An array containing the command line arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("\033[36m@%s: $ ", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

        char input[100];

        while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            printf("Command entered: %s", input);
        }
        else
        {
            printf("Error reading input.\n");
            return 1;
        }

            printf("%s ~$ ", cwd);
    }

    (void)argc;
    (void)argv;

    return 0;
}
