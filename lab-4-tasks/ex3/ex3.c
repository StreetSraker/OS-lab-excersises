#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// Объявляем внешнюю переменную окружения (нужна для execve)
extern char **environ;

int main() {
    char line[1024];
    char *args[64];

    while (1) {
        printf("WhatTheShell> ");
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

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "exit") == 0) break;

        pid_t pid = fork();

        if (pid == 0) {
            char full_path[1024];
            if (args[0][0] == '/' || args[0][0] == '.') {
                strcpy(full_path, args[0]);
            } else {
                snprintf(full_path, sizeof(full_path), "/bin/%s", args[0]);
            }

            execve(full_path, args, environ);
            
            perror("Error");
            exit(1);
        } 
        else if (pid > 0) {
            printf("[Background process, PID: %d]\n", pid);
        }
    }
    return 0;
}
