#include "shell.h"

int execute_command(char *args[])
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erreur lors de la création du processus fils\n");
        return 1;
    }

    if (pid == 0) { /* Processus fils */
        /* Exécuter la commande */
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "Erreur lors de l'exécution de la commande\n");
            exit(EXIT_FAILURE);
        }
    } else { /* Processus parent */
        /* Attendre la fin du processus fils */
        wait(NULL);
    }
    return (0);
}
