#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

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

    return 0;
}

int main() {
    char command[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int should_run = 1;
    pid_t pid;
    char *token;
    int i;

    while (should_run) {
        /* Lire la commande de l'utilisateur */
        printf("\033[36m@%s: $ ", getenv("PWD"));
        fflush(stdout);

        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) {
            break;  
        }

        command[strcspn(command, "\n")] = '\0'; /* Supprimer le saut de ligne final */

        /* Quitter si la commande est "exit" */
        if (strcmp(command, "exit") == 0) {
            should_run = 0;
            continue;
        }

        /* Tokenize la commande */
        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execute_command(args);
    }
    return (0);
}
