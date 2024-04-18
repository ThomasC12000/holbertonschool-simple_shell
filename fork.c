#include "shell.h"

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
        char *envp[] = { NULL };
        if (execve(args[0], args, envp) == -1) 
        {
            fprintf(stderr, "Erreur lors de l'exécution de la commande\n");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        wait(NULL);
    }
    return (0);
}
