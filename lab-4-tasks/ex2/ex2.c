#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please, enter the number of forks, like this:\n%s <number_of_forks>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        fork();
        sleep(5);
    }

    return 0;
}
