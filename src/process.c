#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "process.h"
void run_process_demo(void)
{
    pid_t pid;
    int status;

    printf("\n========== PROCESS MANAGEMENT DEMO ==========\n");

    // Create child process
    pid = fork();

    if(pid < 0)
    {
        perror("fork failed");
        return;
    }

    // Child process
    if(pid == 0)
    {
        printf("\nChild Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("Child process executing successfully.\n");

        printf("Child process simulating failure...\n");
        exit(0);
    }

    // Parent process
    else
    {
        printf("\nParent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Created Child PID: %d\n", pid);

        // Wait for child process
        waitpid(pid, &status, 0);

        if(WIFEXITED(status))
        {
            printf("\nChild exited with status: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("\nChild terminated abnormally.\n");
        }

        printf("Parent process completed successfully.\n");
    }
}

