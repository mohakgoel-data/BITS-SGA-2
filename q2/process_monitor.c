#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_CHILDREN 5
#define TIMEOUT 3

pid_t child_pids[NUM_CHILDREN];

void handle_sigchld(int sig) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child %d terminated\n", pid);
    }
}

int main() {
    signal(SIGCHLD, handle_sigchld);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0) {
            printf("Child %d started with PID %d\n", i, getpid());
            if (i == 2) {
                sleep(10);
            } else {
                sleep(2);
            }
            exit(0);
        }
        else {
            child_pids[i] = pid;
        }
    }

    sleep(TIMEOUT);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (kill(child_pids[i], 0) == 0) {
            printf("Child %d unresponsive, sending SIGTERM\n", child_pids[i]);
            kill(child_pids[i], SIGTERM);
        }
    }

    sleep(1);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        waitpid(child_pids[i], NULL, WNOHANG);
    }

    printf("Parent process finished monitoring all children\n");
    return 0;
}