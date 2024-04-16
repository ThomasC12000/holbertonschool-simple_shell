#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

int main() {
    char command[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    char *token;
    pid_t pid;
    int status;
	int i = 0;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        /* Parse command and arguments */
        
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        /* Handle built-in commands */
        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "env") == 0) {
            extern char **environ;
            char **env = environ;
            while (*env) {
                printf("%s\n", *env);
                env++;
            }
            continue;
        }

        /* Fork and execute command */
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { /* Child process */
            /* Search for command in PATH */
            execvp(args[0], args);
            /* If execvp fails, print error message */
            fprintf(stderr, "%s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        } else { /* Parent process */
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
