/* three_children.c — Parent creates 3 children and waits for all */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int i;

    for (i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        }

        if (pids[i] == 0) {
            /* Each child sleeps a different duration */
            int duration = (i + 1) * 10;  /* 10, 20, 30 seconds */
            printf("Child %d (PID %d): Sleeping %d seconds.\n", i+1, getpid(), duration);
            sleep(duration);
            printf("Child %d (PID %d): Done.\n", i+1, getpid());
            exit(0);
        }
    }

    /* Parent waits for all 3 children */
    printf("Parent (PID %d): Waiting for all 3 children...\n", getpid());
    for (i = 0; i < 3; i++) {
        wait(NULL);  /* NULL = we don't care about exit status */
        printf("Parent: One child finished.\n");
    }

    printf("Parent: All children done. Exiting.\n");
    return 0;
}
