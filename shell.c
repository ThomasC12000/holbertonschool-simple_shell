#include "shell.h"

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */
int main() 
{
    char command[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int should_run = 1;
    char *token;
    int i;

    while (should_run) 
    {
        printf("\033[36m@%s: $ ", getenv("PWD"));
        fflush(stdout);

        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) 
        {
            break;  
        }

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) 
        {
            should_run = 0;
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
    return 0;
}
