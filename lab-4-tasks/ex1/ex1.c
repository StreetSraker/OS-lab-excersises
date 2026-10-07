#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    clock_t start, end;

    // First child process
    pid_t pid1 = fork();

    if (pid1 == 0) {
        start = clock();
        // Simple time-consuming for-loop
        for (long long i = 0; i <= 2000000000LL; i++); // Pretend to do some work
        end = clock();

        printf("CHILD PROCESS 1 | PID: %d, Parent: %d, Time: %.2f ms\n", 
            getpid(), getppid(), ((double)(end - start) / CLOCKS_PER_SEC) * 1000);
        return 0;
    }

    // Second child process
    pid_t pid2 = fork();

    if (pid2 == 0) {
        start = clock();
        for (long long i = 0; i <= 2000000000LL; i++); // Pretend to do some work again
        end = clock();

        printf("CHILD PROCESS 2 | PID: %d, Parent: %d, Time: %.2f ms\n", 
            getpid(), getppid(), ((double)(end - start) / CLOCKS_PER_SEC) * 1000);
        return 0;
    }

    // Parent (Main) process
    start = clock();
    for (long long i = 0; i <= 2000000000LL; i++); // Same here
    end = clock();

    printf("PARENT PROCESS | PID: %d, Parent: %d, Time: %.2f ms\n", 
        getpid(), getppid(), ((double)(end - start) / CLOCKS_PER_SEC) * 1000);

    return 0;
}
