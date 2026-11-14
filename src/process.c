#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "process.h"
void run_worker(const char *worker_name, int simulate_failure)
{
    pid_t pid;
    int status;

    printf("\n========== %s ==========\n", worker_name);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    // Child process
    if (pid == 0)
    {
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        if (simulate_failure)
        {
            printf("Child simulating controlled failure.\n");

            // Simulated failure: non-zero exit
            exit(1);
        }
        else
        {
            printf("Child executing successfully.\n");
            exit(0);
        }
    }

    // Parent process
    else
    {
        printf("\nParent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Created Child PID: %d\n", pid);

        // Wait for child process
        while (waitpid(pid, &status, 0) == -1)
        {
            if (errno != EINTR)
            {
                perror("waitpid failed");
                return;
            }
        }

        // Check child termination status
        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);

            printf("Child exited with status: %d\n", exit_code);

            if (exit_code == 0)
            {
                printf("Worker completed successfully.\n");
            }
            else
            {
                printf("Worker failure detected!\n");
                printf("Failure exit code: %d\n", exit_code);
            }
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child terminated by signal: %d\n",
                   WTERMSIG(status));
        }

        printf("Parent process completed successfully.\n");
    }
}


void run_process_demo(void)
{
    printf("\n========== PROCESS MANAGEMENT DEMO ==========\n");

    // Test 1: Normal child completion
    run_worker("NORMAL WORKER TEST", 0);

    // Test 2: Controlled simulated failure
    run_worker("SIMULATED FAILURE TEST", 1);
}
