#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    char line[1024];
    char *args[64];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            printf("\n");
            continue;
        }

        if (strcmp(args[0], "exit") == 0) break;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("Error");
            exit(1);
        } 
        else if (pid > 0) {
            printf("[Background process, PID: %d]\n", pid);
            fflush(stdout); 
            
            usleep(10000); 
        }
    }
    return 0;
}
